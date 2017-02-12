//
// Created by Kai on 2017/2/12.
//

#include <stdint.h>
#include <stdio.h>

uint32_t sha256_Ch(uint32_t x, uint32_t y, uint32_t z){ return (x & y) ^ ((~x) & z); }
uint32_t sha256_Maj(uint32_t x, uint32_t y, uint32_t z){ return (x & y) ^ (x & z) ^ (y & z); }
uint32_t sha256_Sigma0(uint32_t x){ return (x >> 2 | x << 30) ^ (x >> 13 | x << 19) ^ (x >> 22 | x << 10); }
uint32_t sha256_Sigma1(uint32_t x){ return (x >> 6 | x << 26) ^ (x >> 11 | x << 21) ^ (x >> 25 | x << 7); }
uint32_t sha256_sigma0(uint32_t x){ return (x >> 7 | x << 25) ^ (x >> 18 | x << 14) ^ (x >> 3); }
uint32_t sha256_sigma1(uint32_t x){ return (x >> 17 | x << 15) ^ (x >> 19 | x << 13) ^ (x >> 10); }

#define SHA256_ROTL(a,b) (((a>>(32-b))&(0x7fffffff>>(31-b)))|(a<<b))
#define SHA256_SR(a,b) ((a>>b)&(0x7fffffff>>(b-1)))
#define SHA256_Ch(x,y,z) ((x&y)^((~x)&z))
#define SHA256_Maj(x,y,z) ((x&y)^(x&z)^(y&z))
#define SHA256_E0(x) (SHA256_ROTL(x,30)^SHA256_ROTL(x,19)^SHA256_ROTL(x,10))
#define SHA256_E1(x) (SHA256_ROTL(x,26)^SHA256_ROTL(x,21)^SHA256_ROTL(x,7))
#define SHA256_O0(x) (SHA256_ROTL(x,25)^SHA256_ROTL(x,14)^SHA256_SR(x,3))
#define SHA256_O1(x) (SHA256_ROTL(x,15)^SHA256_ROTL(x,13)^SHA256_SR(x,10))
int main(){
    printf("%u  %u\n", sha256_Ch(1, 2, 3), SHA256_Ch(1, 2, 3));
    printf("%u  %u\n", sha256_Maj(1234567890, 2345678901, 3456789012), SHA256_Maj(1234567890, 2345678901, 3456789012));
    printf("%u  %u\n", sha256_Sigma0(1234567890), SHA256_E0(1234567890));
    printf("%u  %u\n", sha256_Sigma1(1234567890), SHA256_E1(1234567890));
    printf("%u  %u\n", sha256_sigma0(1234567890), SHA256_O0(1234567890));
    printf("%u  %u\n", sha256_sigma1(1234567890), SHA256_O1(1234567890));
}
