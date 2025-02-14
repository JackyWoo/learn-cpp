#include <chrono>
#include <iostream>
#include <memory>
#include <unordered_map>
#include <vector>
#include <cstring> // For memcpy
#ifdef __SSE4_2__
#    include <immintrin.h>
#endif

using UInt8 = uint8_t;
using UInt64 = uint64_t;
using String = std::string;

inline size_t getCurrentTimestamp()
{
    auto now = std::chrono::steady_clock::now();
    return std::chrono::duration_cast<std::chrono::microseconds>(now.time_since_epoch()).count();
}

template <typename T>
inline T unalignedLoad(const void * address)
{
    T res {};
    memcpy(&res, address, sizeof(res));
    return res;
}

inline UInt64 hashLen16(UInt64 u, UInt64 v)
{
    return std::hash<UInt64>()(u) + std::hash<UInt64>()(v);
}

inline UInt64 shiftMix(UInt64 val)
{
    return val ^ (val >> 47);
}

inline UInt64 rotateByAtLeast1(UInt64 val, UInt8 shift)
{
    return (val >> shift) | (val << (64 - shift));
}

inline size_t hashLessThan8(const char * data, size_t size)
{
    static constexpr UInt64 k2 = 0x9ae16a3b2f90404fULL;
    static constexpr UInt64 k3 = 0xc949d7c7509e6557ULL;

    if (size >= 4)
    {
        UInt64 a = unalignedLoad<uint32_t>(data);
        return hashLen16(size + (a << 3), unalignedLoad<uint32_t>(data + size - 4));
    }

    if (size > 0)
    {
        uint8_t a = data[0];
        uint8_t b = data[size >> 1];
        uint8_t c = data[size - 1];
        uint32_t y = static_cast<uint32_t>(a) + (static_cast<uint32_t>(b) << 8);
        uint32_t z = static_cast<uint32_t>(size) + (static_cast<uint32_t>(c) << 2);
        return shiftMix(y * k2 ^ z * k3) * k2;
    }

    return k2;
}

inline size_t hashLessThan16(const char * data, size_t size)
{
    if (size > 8)
    {
        auto a = unalignedLoad<UInt64>(data);
        auto b = unalignedLoad<UInt64>(data + size - 8);
        return hashLen16(a, rotateByAtLeast1(b + size, static_cast<UInt8>(size))) ^ b;
    }

    return hashLessThan8(data, size);
}

struct CRC32Hash
{
    UInt64 operator() (const String & x) const
    {
#ifdef __SSE4_2__
        const char * pos = x.data();
        size_t size = x.size();

        if (size == 0)
            return 0;

        if (size < 8)
        {
            return static_cast<UInt64>(hashLessThan8(x.data(), x.size()));
        }

        const char * end = pos + size;
        UInt64 res = -1U;

        do
        {
            auto word = unalignedLoad<UInt64>(pos);
            res = static_cast<UInt64>(_mm_crc32_u64(res, word));

            pos += 8;
        } while (pos + 8 < end);

        UInt64 word = unalignedLoad<UInt64>(end - 8);    /// I'm not sure if this is normal.
        res = static_cast<UInt64>(_mm_crc32_u64(res, word));

        return res;
#else
        return std::hash<String>()(x);
#endif
    }
};

struct SIMDHash
{
    size_t operator()(const String & x) const
    {
#ifdef __SSE4_2__
        const char * pos = x.data();
        size_t size = x.size();

        if (size == 0)
            return 0;

        const char * end = pos + size;
        size_t res = -1U;

        while (pos + 8 <= end)
        {
            UInt64 word = unalignedLoad<UInt64>(pos);
            res = _mm_crc32_u64(res, word);
            pos += 8;
        }

        if (pos < end)
        {
            UInt64 word = 0;
            std::memcpy(&word, pos, end - pos);
            res = _mm_crc32_u64(res, word);
        }

        return res;
#else
        return std::hash<String>()(x);
#endif
    }
};


#if defined(__SSE2__)
inline bool compare8(const char * p1, const char * p2)
{
    return 0xFFFF == _mm_movemask_epi8(_mm_cmpeq_epi8(
               _mm_loadu_si128(reinterpret_cast<const __m128i *>(p1)),
               _mm_loadu_si128(reinterpret_cast<const __m128i *>(p2))));
}

inline bool compare64(const char * p1, const char * p2)
{
    return 0xFFFF == _mm_movemask_epi8(
               _mm_and_si128(
                   _mm_and_si128(
                       _mm_cmpeq_epi8(
                           _mm_loadu_si128(reinterpret_cast<const __m128i *>(p1)),
                           _mm_loadu_si128(reinterpret_cast<const __m128i *>(p2))),
                       _mm_cmpeq_epi8(
                           _mm_loadu_si128(reinterpret_cast<const __m128i *>(p1) + 1),
                           _mm_loadu_si128(reinterpret_cast<const __m128i *>(p2) + 1))),
                   _mm_and_si128(
                       _mm_cmpeq_epi8(
                           _mm_loadu_si128(reinterpret_cast<const __m128i *>(p1) + 2),
                           _mm_loadu_si128(reinterpret_cast<const __m128i *>(p2) + 2)),
                       _mm_cmpeq_epi8(
                           _mm_loadu_si128(reinterpret_cast<const __m128i *>(p1) + 3),
                           _mm_loadu_si128(reinterpret_cast<const __m128i *>(p2) + 3)))));
}

inline bool memequalWide(const char * p1, const char * p2, size_t size)
{
    /** The order of branches and the trick with overlapping comparisons
      * are the same as in memcpy implementation.
      * See the comments in base/glibc-compatibility/memcpy/memcpy.h
      */

    if (size <= 16)
    {
        if (size >= 8)
        {
            /// Chunks of 8..16 bytes.
            return unalignedLoad<uint64_t>(p1) == unalignedLoad<uint64_t>(p2)
                && unalignedLoad<uint64_t>(p1 + size - 8) == unalignedLoad<uint64_t>(p2 + size - 8);
        }
        else if (size >= 4)
        {
            /// Chunks of 4..7 bytes.
            return unalignedLoad<uint32_t>(p1) == unalignedLoad<uint32_t>(p2)
                && unalignedLoad<uint32_t>(p1 + size - 4) == unalignedLoad<uint32_t>(p2 + size - 4);
        }
        else if (size >= 2)
        {
            /// Chunks of 2..3 bytes.
            return unalignedLoad<uint16_t>(p1) == unalignedLoad<uint16_t>(p2)
                && unalignedLoad<uint16_t>(p1 + size - 2) == unalignedLoad<uint16_t>(p2 + size - 2);
        }
        else if (size >= 1)
        {
            /// A single byte.
            return *p1 == *p2;
        }
        return true;
    }

    while (size >= 64)
    {
        if (compare64(p1, p2))
        {
            p1 += 64;
            p2 += 64;
            size -= 64;
        }
        else
            return false;
    }

    switch (size / 16) // NOLINT(bugprone-switch-missing-default-case)
    {
        case 3: if (!compare8(p1 + 32, p2 + 32)) return false; [[fallthrough]];
        case 2: if (!compare8(p1 + 16, p2 + 16)) return false; [[fallthrough]];
        case 1: if (!compare8(p1, p2)) return false; [[fallthrough]];
        default: ;
    }

    return compare8(p1 + size - 16, p2 + size - 16);
}

#endif

struct SIMDEquals {
    bool operator()(const std::string& lhs, const std::string& rhs) const
    {
        if (lhs.size() != rhs.size())
            return false;

        if (lhs.empty())
            return true;

#if defined(__SSE2__)
        return memequalWide(lhs.data(), rhs.data(), lhs.size());
#else
        return 0 == memcmp(lhs.data(), rhs.data(), lhs.size());
#endif
    }
};


int main()
{
    size_t n = 100000;
    size_t m = 100;

    std::vector<String> keys;
    keys.reserve(n);

    for (size_t i = 0; i < n; i++)
    {
        String k(std::to_string(i));
        if (k.length() < m)
        {
            String zero(m - k.length(), '0');
            k.append(zero);
        }
        keys.push_back(std::move(k));
    }

    std::unordered_map<String, char, std::hash<String>> map1;
    map1.reserve(3 * n);
    std::unordered_map<String, char, CRC32Hash, SIMDEquals> map2;
    map2.reserve(3 * n);

    auto t1 = getCurrentTimestamp();

    UInt64 hash_v;
    for (const auto & k : keys)
        hash_v = std::hash<String>()(k);

    auto t2 = getCurrentTimestamp();

    for (size_t i = 0; i < n; i++)
        map1.emplace(keys[i], 0);

    auto t3 = getCurrentTimestamp();

    for (size_t i = 0; i < n; i++)
        map1.find(keys[i]);

    auto t4 = getCurrentTimestamp();


    for (const auto & k : keys)
        hash_v = CRC32Hash()(k);

    auto t5 = getCurrentTimestamp();

    for (size_t i = 0; i < n; i++)
        map2.emplace(keys[i], 0);

    auto t6 = getCurrentTimestamp();

    for (size_t i = 0; i < n; i++)
        map2.find(keys[i]);

    auto t7 = getCurrentTimestamp();

    std::cout << "Generate hash time " << std::to_string(t2 - t1) << "us" << std::endl;
    std::cout << "Emplace hash map time " << std::to_string(t3 - t2) << "us" << std::endl;
    std::cout << "Find hash map time " << std::to_string(t4 - t3) << "us" << std::endl;

    std::cout << "Generate hash with SIMD time " << std::to_string(t5 - t4) << "us" << std::endl;
    std::cout << "Emplace hash map with SIMD hash time " << std::to_string(t6 - t5) << "us" << std::endl;
    std::cout << "Find hash map with SIMD hash time " << std::to_string(t7 - t6) << "us" << std::endl;

    return 0;
}
