/*
* MrThomasLibrary
* RSA encryption for Kevlar Encryption
* February 2026
*
*/

#define BASE 256
#define BASIS 10000

#include <inttypes.h>
#include <math.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

bool get_decryption_key(uint64_t e, uint64_t phi, uint64_t *d);
bool isPrime(int n);

uint32_t nthPrime(int n);

uint64_t gcd(uint64_t n, uint64_t m);
uint64_t mul_mod(uint64_t n, uint64_t m, uint64_t mod);
uint64_t modular_pow(uint64_t base, uint64_t exp, uint64_t mod);

int64_t extended_gcd(int64_t a, int64_t b, int64_t *x, int64_t *y);

void createCharKey(uint64_t* e, uint64_t* d, uint64_t* n);
void createKeys(char* name);
void decryptFile(char* infile, char* privateKey, char* outname);
void encryptFile(char* infile, char* publicKey, char* outname);
