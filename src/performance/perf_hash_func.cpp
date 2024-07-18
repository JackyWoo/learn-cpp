#include <iostream>
#include <vector>
#include <unordered_map>
#include <nmmintrin.h>

using UInt64 = uint64_t;

inline size_t getCurrentTimestamp()
{
    auto now = std::chrono::system_clock::now();
    return std::chrono::duration_cast<std::chrono::microseconds>(now.time_since_epoch()).count();
}

/** Taken from MurmurHash. This is Murmur finalizer.
  * Faster than intHash32 when inserting into the hash table UInt64 -> UInt64, where the key is the visitor ID.
  */
inline UInt64 intHash64(UInt64 x)
{
    x ^= x >> 33;
    x *= 0xff51afd7ed558ccdULL;
    x ^= x >> 33;
    x *= 0xc4ceb9fe1a85ec53ULL;
    x ^= x >> 33;

    return x;
}

/// NOTE: Intel intrinsic can be confusing.
/// - https://code.google.com/archive/p/sse-intrinsics/wikis/PmovIntrinsicBug.wiki
/// - https://stackoverflow.com/questions/15752770/mm-crc32-u64-poorly-defined
inline UInt64 intHashCRC32(UInt64 x)
{
#ifdef __SSE4_2__
    return _mm_crc32_u64(-1ULL, x);
#endif
    throw std::exception();
}

int main()
{
    size_t n = 1000000;


    auto t1 = getCurrentTimestamp();

    for (size_t i=0; i< n; i++)
        std::hash<UInt64>()(i);

    auto t2 = getCurrentTimestamp();

    for (size_t i=0; i< n; i++)
        intHashCRC32(i);

    auto t3 = getCurrentTimestamp();

    std::cout << "Standard hash time " << std::to_string(t2 - t1) << "us" << std::endl;
    std::cout << "intHashCRC32 hash time " << std::to_string(t3 - t2) << "us" << std::endl;

}
