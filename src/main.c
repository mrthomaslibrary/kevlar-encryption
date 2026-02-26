#include "../include/rsa.h"

//#include <stdio.h>
#include <time.h>

int main(int argc, char* argv[]) {
  srand(time(NULL));
  createKeys("MyKey");

  encryptFile("test_plain_text.txt", "MyKey_public.key", "encyptedtext");
  decryptFile("encyptedtext_secure.rsenc", "MyKey_private.key", "decryptedtext");

  //printf("%"PRIu64, modular_pow(72, 65573, 40903));
  
}
