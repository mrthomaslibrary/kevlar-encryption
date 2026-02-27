#ifndef RSA_H
#define RSA_H

#define BASIS 10000
#define BASE 256

#include "../include/hashoffset.h"

uint64_t totient(uint64_t n);
uint64_t gcd(uint64_t n, uint64_t m);

void createCharKey(uint64_t* e, uint64_t* d, uint64_t* n);
void createKeys(char* name, char* password);
bool get_decryption_key(uint64_t e, uint64_t phi, uint64_t *d);
int64_t extended_gcd(int64_t a, int64_t b, int64_t *x, int64_t *y);
uint64_t mul_mod(uint64_t a, uint64_t b, uint64_t m);
uint64_t modular_pow(uint64_t base, uint64_t exp, uint64_t mod);
void encryptFile(char* infile, char* publicKey, char* outname);
void decryptFile(char* infile, char* privateKey, char* outname);

#endif
