#pragma once

/** SipHash is a fast cryptographic hash function for short strings.
  * Taken from here: https://www.131002.net/siphash/
  *
  * This is SipHash 2-4 variant.
  *
  * Two changes are made:
  * - returns also 128 bits, not only 64;
  * - done streaming (can be calculated in parts).
  *
  * On short strings (URL, search phrases) more than 3 times faster than MD5 from OpenSSL.
  * (~ 700 MB/sec, 15 million strings per second)
  */

#include <bit>
#include <string>
#include <type_traits>
#include <algorithm>

namespace DB::ErrorCodes
{
extern const int LOGICAL_ERROR;
}

#define SIPROUND                                                  \
    do                                                            \
    {                                                             \
        v0 += v1; v1 = std::rotl(v1, 13); v1 ^= v0; v0 = std::rotl(v0, 32); \
        v2 += v3; v3 = std::rotl(v3, 16); v3 ^= v2;                    \
        v0 += v3; v3 = std::rotl(v3, 21); v3 ^= v0;                    \
        v2 += v1; v1 = std::rotl(v1, 17); v1 ^= v2; v2 = std::rotl(v2, 32); \
    } while(0)

/// Define macro CURRENT_BYTES_IDX for building index used in current_bytes array
/// to ensure correct byte order on different endian machines
#if __BYTE_ORDER__ == __ORDER_BIG_ENDIAN__
#define CURRENT_BYTES_IDX(i) (7 - i)
#else
#define CURRENT_BYTES_IDX(i) (i)
#endif

inline void reverseMemcpy(void * dst, const void * src, size_t size)
{
    uint8_t * uint_dst = reinterpret_cast<uint8_t *>(dst);
    const uint8_t * uint_src = reinterpret_cast<const uint8_t *>(src);

    uint_dst += size;
    while (size)
    {
        --uint_dst;
        *uint_dst = *uint_src;
        ++uint_src;
        --size;
    }
}

template <std::endian endian, typename T>
inline T unalignedLoadEndian(const void * address)
{
    T res {};
    if constexpr (std::endian::native == endian)
        memcpy(&res, address, sizeof(res));
    else
        reverseMemcpy(&res, address, sizeof(res));
    return res;
}

template <typename T>
inline T unalignedLoadLittleEndian(const void * address)
{
    return unalignedLoadEndian<std::endian::little, T>(address);
}

class SipHash
{
private:
    /// State.
    uint64_t v0;
    uint64_t v1;
    uint64_t v2;
    uint64_t v3;

    /// How many bytes have been processed.
    uint64_t cnt;

    /// Whether it should use the reference algo for 128-bit or CH's version
    bool is_reference_128;

    /// The current 8 bytes of input data.
    union
    {
        uint64_t current_word;
        uint8_t current_bytes[8];
    };

    inline void finalize()
    {
        /// In the last free byte, we write the remainder of the division by 256.
        current_bytes[CURRENT_BYTES_IDX(7)] = static_cast<uint8_t>(cnt);

        v3 ^= current_word;
        SIPROUND;
        SIPROUND;
        v0 ^= current_word;

        if (is_reference_128)
            v2 ^= 0xee;
        else
            v2 ^= 0xff;
        SIPROUND;
        SIPROUND;
        SIPROUND;
        SIPROUND;
    }

public:
    /// Arguments - seed.
    SipHash(uint64_t key0 = 0, uint64_t key1 = 0, bool is_reference_128_ = false) /// NOLINT
    {
        /// Initialize the state with some random bytes and seed.
        v0 = 0x736f6d6570736575ULL ^ key0;
        v1 = 0x646f72616e646f6dULL ^ key1;
        v2 = 0x6c7967656e657261ULL ^ key0;
        v3 = 0x7465646279746573ULL ^ key1;
        is_reference_128 = is_reference_128_;

        if (is_reference_128)
            v1 ^= 0xee;

        cnt = 0;
        current_word = 0;
    }

    inline void update(const char * data, uint64_t size)
    {
        const char * end = data + size;

        /// We'll finish to process the remainder of the previous update, if any.
        if (cnt & 7)
        {
            while (cnt & 7 && data < end)
            {
                current_bytes[CURRENT_BYTES_IDX(cnt & 7)] = *data;
                ++data;
                ++cnt;
            }

            /// If we still do not have enough bytes to an 8-byte word.
            if (cnt & 7)
                return;

            v3 ^= current_word;
            SIPROUND;
            SIPROUND;
            v0 ^= current_word;
        }

        cnt += end - data;

        while (data + 8 <= end)
        {
            current_word = unalignedLoadLittleEndian<uint64_t>(data);

            v3 ^= current_word;
            SIPROUND;
            SIPROUND;
            v0 ^= current_word;

            data += 8;
        }

        /// Pad the remainder, which is missing up to an 8-byte word.
        current_word = 0;
        switch (end - data) /// NOLINT(bugprone-switch-missing-default-case)
        {
            case 7: current_bytes[CURRENT_BYTES_IDX(6)] = data[6]; [[fallthrough]];
            case 6: current_bytes[CURRENT_BYTES_IDX(5)] = data[5]; [[fallthrough]];
            case 5: current_bytes[CURRENT_BYTES_IDX(4)] = data[4]; [[fallthrough]];
            case 4: current_bytes[CURRENT_BYTES_IDX(3)] = data[3]; [[fallthrough]];
            case 3: current_bytes[CURRENT_BYTES_IDX(2)] = data[2]; [[fallthrough]];
            case 2: current_bytes[CURRENT_BYTES_IDX(1)] = data[1]; [[fallthrough]];
            case 1: current_bytes[CURRENT_BYTES_IDX(0)] = data[0]; [[fallthrough]];
            case 0: break;
        }
    }

    template <typename Transform = void, typename T>
    inline void update(const T & x)
    {
        if constexpr (std::endian::native == std::endian::big)
        {
            auto transformed_x = x;
            if constexpr (!std::is_same_v<Transform, void>)
                transformed_x = Transform()(x);
            else
                std::transform(std::begin(transformed_x), std::end(transformed_x), std::begin(transformed_x), [](auto & item) { return std::byteswap(item); });

            update(reinterpret_cast<const char *>(&transformed_x), sizeof(transformed_x)); /// NOLINT
        }
        else
            update(reinterpret_cast<const char *>(&x), sizeof(x)); /// NOLINT
    }

    inline void update(const std::string & x) { update(x.data(), x.length()); }
    inline void update(const std::string_view x) { update(x.data(), x.size()); }
    inline void update(const char * s) { update(std::string_view(s)); }

    inline uint64_t get64()
    {
        finalize();
        return v0 ^ v1 ^ v2 ^ v3;
    }

    template <typename T>
        requires (sizeof(T) == 8)
    inline void get128(T & lo, T & hi)
    {
        finalize();
        lo = v0 ^ v1;
        hi = v2 ^ v3;
    }

};


#undef ROTL
#undef SIPROUND

#include <cstddef>

inline uint64_t sipHash64Keyed(uint64_t key0, uint64_t key1, const char * data, const size_t size)
{
    SipHash hash(key0, key1);
    hash.update(data, size);
    return hash.get64();
}

inline uint64_t sipHash64(const char * data, const size_t size)
{
    return sipHash64Keyed(0, 0, data, size);
}

template <typename T>
inline uint64_t sipHash64(const T & x)
{
    SipHash hash;
    hash.update(x);
    return hash.get64();
}

inline uint64_t sipHash64(const std::string & s)
{
    return sipHash64(s.data(), s.size());
}

#undef CURRENT_BYTES_IDX
