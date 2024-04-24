//
// Created by wujianchao5 on 2024/4/9.
//
#include <iostream>
#include <immintrin.h>
#include <string>

void toUpperCaseSSE(std::string &s) {
    const int chunk_size = 16;  // SSE register size is 16 bytes
    const int len = s.length();

    int batch_end = len / chunk_size * chunk_size;
    for (int i = 0; i < batch_end; i += chunk_size) {
        // Load 16 characters into an SSE register
        __m128i chunk = _mm_loadu_si128(reinterpret_cast<const __m128i *>(&s[i]));

        // Define masks for lowercase letters
        __m128i lowerMask = _mm_cmpgt_epi8(_mm_set1_epi8('a' - 1), chunk);
        __m128i upperMask = _mm_cmpgt_epi8(chunk, _mm_set1_epi8('z'));

        // Apply masks to convert lowercase letters to uppercase
        __m128i result = _mm_blendv_epi8(chunk, _mm_sub_epi8(chunk, _mm_set1_epi8(32)), lowerMask);
        result = _mm_blendv_epi8(result, chunk, upperMask);

        // Store the result back to the string
        _mm_storeu_si128(reinterpret_cast<__m128i *>(&s[i]), result);
    }

    for (int i = batch_end; i < len; i++) {
        if (s[i] >= 'a' && s[i] <= 'z') {
            s[i] -= 32;
        }
    }
}

int main() {
    std::string input = "Hello, World! This is a test string for AVX-512 uppercase conversion.";
    std::cout << "Original: " << input << std::endl;
    toUpperCaseSSE(input);
    std::cout << "Uppercase: " << input << std::endl;
    return 0;
}