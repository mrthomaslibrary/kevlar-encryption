#include "../include/rsa.h"

//Given e and phi(n), generates a d that is usable
bool get_decryption_key(uint64_t e, uint64_t phi_n, uint64_t* d) {
    int64_t x, y;
    uint64_t gcd = extended_gcd(e, phi_n, &x, &y);
    if (gcd != 1) { return false; }
    int64_t d_signed = x % (int64_t)phi_n;
    if (d_signed < 0) { d_signed += (int64_t)phi_n; }
    *d = (uint64_t)d_signed;
    return true;
}

//returns true if n is prime
bool isPrime(int n) {
  if (n < 2) {  return false; }
    if (n == 2 || n == 3) { return true;  }
    if (n % 2 == 0 || n % 3 == 0) { return false; }
    for (int i = 5; i * i <= n; i += 6) {
        if (n % i == 0 || n % (i + 2) == 0) { return false; }
    }
    return true;  
}

//returns the nth number in the sequence of prime numbers
uint32_t nthPrime(int n) {
  if (n < 1) {  return -1;  }
    int count = 0;
    int candidate = 1;
    while (count < n) {
        candidate += 1;
        if (isPrime(candidate)) { count++;  }
    }
    return candidate;  
}

//returns the greatest common denominator of n and m
uint64_t gcd(uint64_t n, uint64_t m) {
  while (m) {
        n %= m;
        uint64_t tmp = n;
        n = m;
        m = tmp;
    }
    return n;
}

//using 64-bit integers calculates
uint64_t mul_mod(uint64_t n, uint64_t m, uint64_t mod) {
  uint64_t res = 0;
    n %= mod;
    while (m > 0) {
        if (m % 2 == 1) {
          if (res >= mod - n) res -= mod; 
          res = (res + n) % mod;
        }
        if (n >= mod - n) n -= mod;
        n = (n + n) % mod;
        m /= 2;
    }
    return res;   
}

//using 64-bit integers calculates (base^exp % mod)
uint64_t modular_pow(uint64_t base, uint64_t exp, uint64_t mod) {
 uint64_t result = 1;
    
    base %= mod;
    if (base == 0) return 0;   
    while (exp > 0) {
        if (exp & 1) {
            result = ((unsigned __int128)result * base) % mod;
        }
        base = ((unsigned __int128)base * base) % mod;
        exp >>= 1;
    }

    return result; 
}

//Finds the greatest common denominator for signed 64-bit integers
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

//Creates a single instance of encryption / decryption keys
void createCharKey(uint64_t* e, uint64_t* d, uint64_t *n) {
  
  uint64_t p, q; 
  uint64_t phi;

  //Create random key pair
  do {
    p = nthPrime(rand() % BASIS + 256);
    do {
      q = nthPrime(rand() % BASIS + 256);
    } while (p == 1);
    *n = p*q;
    phi = (uint64_t)(p - 1) * (uint64_t)(q - 1);  
    *e = nthPrime(rand() % 1000 + 1);

    //Repeat this while 2 < e < phi(n)
  } while (2 > *e || *e > phi || gcd(*e, phi) != 1);

  //Create random decryption key until valid
  do {} while (!get_decryption_key(*e, phi, d));  
}

//Creates two files, a public key and a private keys and saves them as files
void createKeys(char* name) {

  //Open files
  char publicname[256];
  char privatename[256];
  snprintf(publicname, sizeof(publicname), "%s_public.key", name);
  snprintf(privatename, sizeof(privatename), "%s_private.key", name);
  FILE* publicKey = fopen(publicname, "w");
  FILE* privateKey = fopen(privatename, "w");
  if (publicKey == NULL || privateKey == NULL) {
    printf("Error creating key files\n");
  }
  //Crate key pairs and write them to files
  else {
    for (int i = 0; i < BASE; i++) {
       uint64_t e, d, n;
       createCharKey(&e, &d, &n);
       fprintf(publicKey, "%" PRIu64 " %" PRIu64 " ", e, n);
       fprintf(privateKey, "%" PRIu64 " %" PRIu64 " ", d, n);
    }

    //Close files
    fclose(publicKey);
    fclose(privateKey);
  }
}

//Uses decryption keys to decrypt and encrypted file and then saves it as a file
void decryptFile(char* infile, char* privateKey, char* outname) {

  //Load files
  FILE* cyphertext = fopen(infile, "r");
  FILE* decryptionKey = fopen(privateKey, "r");
  char decryptedname[256];
  snprintf(decryptedname, sizeof(decryptedname), "%s.txt", outname);
  FILE* outfile = fopen(decryptedname, "w");

  //Check if files open
  if (cyphertext == NULL || decryptionKey == NULL || outfile == NULL) {
    printf("Failed to open/create files\n");
    if (cyphertext) fclose(cyphertext);
    if (decryptionKey) fclose(decryptionKey);
  } else {

    //Load decryption key
    uint64_t d[BASE];
    uint64_t n[BASE];
    char line[8192];
    int keys_read = 0;
    if(fgets(line, sizeof(line), decryptionKey)){
      
      char *token = strtok(line, " \n\r");

      for (int i = 0; i < BASE && token != NULL; i++) {
        d[i] = strtoull(token, NULL, 10);
        token = strtok(NULL, " \n\r");
        if (token == NULL) break;
        n[i] = strtoull(token, NULL, 10); 
        token = strtok(NULL, " \n\r");
        keys_read += 1;
      }
    }

    //Decrypt file
    int k = 0;
    while(fgets(line, sizeof(line), cyphertext)) {
      char* token = strtok(line, " \n\r");
      while (token != NULL) {
        uint64_t val = strtoull(token, NULL, 10);
        uint64_t decrypted_val = modular_pow(val, d[k % keys_read], n[k % keys_read]);
        fputc((char)decrypted_val, outfile);
        k += 1;
        token = strtok(NULL, " \n\r");
      }
    }
    
    //Close files
    fclose(cyphertext);
    fclose(decryptionKey);
    fclose(outfile);
  }
}

//Uses encryption keys to encrypt a decrypted file and then saves it
void encryptFile(char* infile, char* publicKey, char* outname) {

  //Open files
  FILE* plaintext = fopen(infile, "r");
  FILE* encryptionKey = fopen(publicKey, "r");
  char encryptedname[256];
  snprintf(encryptedname, sizeof(encryptedname), "%s_secure.rsenc", outname);
  FILE* outfile = fopen(encryptedname, "w");

  //Check if files open correctly
  if (plaintext == NULL || encryptionKey == NULL || outfile == NULL) {
    printf("Failed to open/create files\n");
  } else {

    //Load encryption key
    uint64_t e[BASE];
    uint64_t n[BASE];
    char line[100000];
    fgets(line, sizeof(line), encryptionKey);
    char *token = strtok(line, " \n\r");
    int keys_read = 0;
    for (int i = 0; i < BASE; i++) {
      if (token == NULL) break;
      e[i] = strtoull(token, NULL, 10);
      token = strtok(NULL, " \n\r");
      if (token == NULL) break;
      n[i] = strtoull(token, NULL, 10); 
      token = strtok(NULL, " \n\r");
      keys_read += 1;
    }

    //Encrypt file using encryptino key
    int k = 0;
    while(fgets(line, sizeof(line), plaintext)) {    
      for (int i = 0; i < strlen(line); i++) {
        uint64_t value = (uint64_t) (unsigned char) line[i];
        uint64_t index = modular_pow((uint64_t) value, e[k % keys_read], n[k % keys_read]);
       
        fprintf(outfile, "%" PRIu64 " ", index);
        k += 1;
      }
    }

    //Close files
    fclose(plaintext);
    fclose(encryptionKey);
    fclose(outfile);
  }
}


