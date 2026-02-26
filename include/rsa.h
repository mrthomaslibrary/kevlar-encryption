#define BASIS 100

#include <inttypes.h>
#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

uint64_t totient(uint64_t n);
uint64_t gcd(uint64_t n, uint64_t m);
uint32_t nthPrime(int n);
int isPrime(int n);

void createCharKey(uint64_t* e, uint64_t* d);
void createKeys(char* name);
uint64_t get_decryption_key(uint64_t e, uint64_t phi);
int64_t extended_gcd(int64_t a, int64_t b, int64_t *x, int64_t *y);
