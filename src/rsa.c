#include "../include/rsa.h"

int totient(int n) {
  int result = 1;
  for (int i = 2; i < n; i++) {
    if (gcd(i, n) == 1) result++;
  }
  return result;
}

int gcd(int n, int m) {
  if (n == 0) return m;
  return gcd(m % n, n);
}

int nthPrime(int n) {
  int k = 1;
  int j = 2;
  while (k <= n) {
    if (isPrime(j) == 1)  k += 1;
  }
  return j;
}

int isPrime(int n) {
  int k = 1;
  for (int i = 2; i < sqrt(n); i++) {
    if (n % i == 0) {
      k = 0;
    }
  }
  return k;
}

