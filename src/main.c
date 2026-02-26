#include "../include/rsa.h"

//#include <stdio.h>
#include <time.h>

int main(int argc, char* argv[]) {
  srand(time(NULL));
  createKeys("MyKey");

  //uint32_t n = nthPrime(15);
  //printf("%d\n", n);

}
