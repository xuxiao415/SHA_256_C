#include <stdio.h>
#include <stdint.h>

//
// Created by Kai on 2017/2/10.
//
uint32_t sha256_Ch(uint32_t x, uint32_t y, uint32_t z){ return (x & y) ^ ((~x) & z); }
uint32_t sha256_Maj(uint32_t x, uint32_t y, uint32_t z){ return (x & y) ^ (x & z) ^ (y & z); }
uint32_t sha256_Sigma0(uint32_t x){ return (x >> 2 | x << 30) ^ (x >> 13 | x << 19) ^ (x >> 22 | x << 10); }
uint32_t sha256_Sigma1(uint32_t x){ return (x >> 6 | x << 26) ^ (x >> 11 | x << 21) ^ (x >> 25 | x << 7); }
uint32_t sha256_sigma0(uint32_t x){ return (x >> 7 | x << 25) ^ (x >> 18 | x << 14) ^ (x >> 3); }
uint32_t sha256_sigma1(uint32_t x){ return (x >> 17 | x << 15) ^ (x >> 19 | x << 13) ^ (x >> 10); }

int main() {
    uint8_t M[64]={
            97, 98, 99, 128, 0, 0, 0, 0,
            0, 0, 0, 0, 0, 0, 0, 0,
            0, 0, 0, 0, 0, 0, 0, 0,
            0, 0, 0, 0, 0, 0, 0, 0,
            0, 0, 0, 0, 0, 0, 0, 0,
            0, 0, 0, 0, 0, 0, 0, 0,
            0, 0, 0, 0, 0, 0, 0, 0,
            0, 0, 0, 0, 0, 0, 0, 24,
    };
    uint32_t W[64];
    uint32_t H[8] = { 0x6a09e667, 0xbb67ae85, 0x3c6ef372, 0xa54ff53a, 0x510e527f, 0x9b05688c, 0x1f83d9ab, 0x5be0cd19 };
    uint32_t K[64] = {
            0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5, 0x3956c25b, 0x59f111f1, 0x923f82a4, 0xab1c5ed5,
            0xd807aa98, 0x12835b01, 0x243185be, 0x550c7dc3, 0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174,
            0xe49b69c1, 0xefbe4786, 0x0fc19dc6, 0x240ca1cc, 0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da,
            0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7, 0xc6e00bf3, 0xd5a79147, 0x06ca6351, 0x14292967,
            0x27b70a85, 0x2e1b2138, 0x4d2c6dfc, 0x53380d13, 0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85,
            0xa2bfe8a1, 0xa81a664b, 0xc24b8b70, 0xc76c51a3, 0xd192e819, 0xd6990624, 0xf40e3585, 0x106aa070,
            0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5, 0x391c0cb3, 0x4ed8aa4a, 0x5b9cca4f, 0x682e6ff3,
            0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208, 0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2,
    };
    uint32_t a, b, c, d, e, f, g, h, T1, T2;
    uint32_t M1, M2, M3, M4;
    //uint64_t N;
    int i, j, k, l;
    for(i = 0; i < 1; i++){
        a = H[0];
        b = H[1];
        c = H[2];
        d = H[3];
        e = H[4];
        f = H[5];
        g = H[6];
        h = H[7];
        for (k = 0, l = 0; k < 16; ++k, l += 4) {
            M1 = M[l], M2 = M[l+1], M3 = M[l+2], M4 = M[l+3];
            W[k] = M1 * 256 * 256 * 256 + M2 * 256 * 256 + M3 * 256 + M4;
            printf("%u ", W[k]);
        }
        printf("\n");

        for (k = 16; k < 64; k++) {
            W[k] = sha256_sigma1(W[k-2]) + W[k-7] + sha256_sigma0(W[k-15]) + W[k-16];
            printf("%u ", W[k]);
        }
        printf("\n");
        for(j = 0; j < 64; j++){
            printf("%X  %X  %X  %X  %X  %X  %X  %X\n", a, b, c, d, e, f, g, h);
            T1 = h + sha256_Sigma1(e) + sha256_Ch(e, f, g) + K[j] + W[j];
            T2 = sha256_Sigma0(a) + sha256_Maj(a, b, c);
            h = g;
            g = f;
            f = e;
            e = d + T1;
            d = c;
            c = b;
            b = a;
            a = T1 + T2;
        }
        H[0] += a;
        H[1] += b;
        H[2] += c;
        H[3] += d;
        H[4] += e;
        H[5] += f;
        H[6] += g;
        H[7] += h;
    }
    printf("%X%X%X%X%X%X%X%X\n", H[0], H[1], H[2], H[3], H[4], H[5], H[6], H[7]);
    return 0;
}