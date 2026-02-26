#include "../include/rsa.h"

uint64_t totient(uint64_t n) {
  uint64_t result = 1;
  for (int i = 2; i < n; i++) {
    if (gcd(i, n) == 1) result++;
  }
  return result;
}

uint64_t gcd(uint64_t n, uint64_t m) {
  if (n == 0) return m;
  return gcd(m % n, n);
}

long long long_gcd(long long n , long long m) {
  if (n == 0) return m;
  return gcd(m % n, n);
}

uint32_t nthPrime(int n) {
  int k = 1;
  int l = 0;
  while (k <= n) {
    if (isPrime(l) == 1) {
      k += 1;
    }
    l += 1;
  }
  return l;
}

int isPrime(int n) {
  int k = 1;
  for (int i = 2; i < n; i++) {
    if (n % i == 0) {
      k = 0;
    }
  }
  return k;
}

void createCharKey(uint64_t* e, uint64_t* d) {
  
  uint32_t p, q; 
  uint64_t n, phi = (p - 1) * (q - 1);

  do {
    p = nthPrime(rand() % BASIS + 1);
    q = nthPrime(rand() % BASIS + 1);
    n = p*q;
    phi = (uint64_t)(p - 1) * (uint64_t)(q - 1);

   
    *e = nthPrime(rand() % 1000 + 1);
    
  } while (gcd(*e, phi) != 1);

  *d = get_decryption_key(*e, phi);
}

uint64_t get_decryption_key(uint64_t e, uint64_t phi) {
    int64_t d, y;
    uint64_t g = extended_gcd((int64_t)e, (int64_t)phi, &d, &y);

    if (g != 1) {   return 0;  }
    else {  return (uint64_t)(d % (int64_t)phi + (int64_t)phi) % (int64_t)phi;  }
}

int64_t extended_gcd(int64_t a, int64_t b, int64_t *x, int64_t *y) {
    if (a == 0) {
        *x = 0;
        *y = 1;
        return b;
    }

    int64_t x1, y1;
    int64_t gcd = extended_gcd(b % a, a, &x1, &y1);

    *x = y1 - (b / a) * x1;
    *y = x1;

    return gcd;
}

void createKeys(char* name) {
  char publicname[256];
  char privatename[256];
  snprintf(publicname, sizeof(publicname), "%s_public.key", name);
  snprintf(privatename, sizeof(privatename), "%s_private.key", name);
  FILE* publicKey = fopen(publicname, "w");
  FILE* privateKey = fopen(privatename, "w");

  if (publicKey == NULL || privateKey == NULL) {
    printf("Error creating key files\n");
  }
  else {
    for (int i = 0; i < 256; i++) {
       uint64_t e, d;
       createCharKey(&e, &d);
       fprintf(publicKey, "%" PRIu64 " ", e);
       fprintf(privateKey, "%" PRIu64 " ", d);
    }
    fclose(publicKey);
    fclose(privateKey);
  }
}
