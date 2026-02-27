#ifndef HASHOFFSET_H
#define HASHOFFSET_H

#include <stdbool.h>
#include <inttypes.h>
#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

uint32_t nthPrime(int n);
bool isPrime(int n);
char* hashPassword(char* password);
uint32_t hashToPrime(char* hash);
uint32_t offsetCreation(char* password);

#endif