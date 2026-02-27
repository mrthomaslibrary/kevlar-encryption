#include "../include/rsa.h"

uint64_t totient(uint64_t n) {
  uint64_t result = 1;
  for (int i = 2; i < n; i++) {
    if (gcd(i, n) == 1) result++;
  }
  return result;
}

uint64_t gcd(uint64_t n, uint64_t m) {
  while (m) {
        n %= m;
        uint64_t tmp = n;
        n = m;
        m = tmp;
    }
    return n;
}

long long long_gcd(long long n , long long m) {
  if (n == 0) return m;
  return gcd(m % n, n);
}

uint64_t mul_mod(uint64_t a, uint64_t b, uint64_t mod) {
  uint64_t res = 0;
    a %= mod;
    while (b > 0) {
        if (b % 2 == 1) {
            // Safe addition: (res + a) % mod
            if (res >= mod - a) res -= mod; 
            res = (res + a) % mod;
        }
        // Safe doubling: (a * 2) % mod
        if (a >= mod - a) a -= mod;
        a = (a + a) % mod;
        b /= 2;
    }
    return res;   
}

void createCharKey(uint64_t* e, uint64_t* d, uint64_t *n) {
  
  uint64_t p, q; 
  uint64_t phi;

  do {
    p = nthPrime(rand() % BASIS + 256);
    do {
      q = nthPrime(rand() % BASIS + 256);
    } while (p == 1);
    *n = p*q;
    phi = (uint64_t)(p - 1) * (uint64_t)(q - 1);

   
    *e = nthPrime(rand() % 1000 + 1);
    
  } while (2 > *e || *e > phi || gcd(*e, phi) != 1);

  do {} while (!get_decryption_key(*e, phi, d)); 
 
}

bool get_decryption_key(uint64_t e, uint64_t phi_n, uint64_t* d)
{
    int64_t x, y;
    uint64_t gcd = extended_gcd(e, phi_n, &x, &y);

    if (gcd != 1) {
        // e and φ(n) are not coprime → no inverse exists
        return false;
    }

    // x might be negative → make it positive modulo φ(n)
    int64_t d_signed = x % (int64_t)phi_n;
    if (d_signed < 0) {
        d_signed += (int64_t)phi_n;
    }

    *d = (uint64_t)d_signed;
    return true;
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

void createKeys(char* name, char* password) {
    char publicname[256], privatename[256];
    int offset = offsetCreation(password);

    snprintf(publicname, sizeof(publicname), "%s_public.key", name);
    snprintf(privatename, sizeof(privatename), "%s_private.key", name);

    FILE* publicKey = fopen(publicname, "w");
    FILE* privateKey = fopen(privatename, "w");

    if (publicKey == NULL || privateKey == NULL) {
        printf("Error creating key files\n");
    }
    else {
        for (int i = 0; i < BASE; i++) {
            uint64_t e, d, n;
            createCharKey(&e, &d, &n);
            fprintf(publicKey, "%" PRIu64 " %" PRIu64 " ", e, n);
            fprintf(privateKey, "%" PRIu64 " %" PRIu64 " ",  rotate(d, offset, LEFT), n);
        }

        fclose(publicKey);
        fclose(privateKey);
  }
}

uint64_t modular_pow(uint64_t base, uint64_t exp, uint64_t mod) {
 uint64_t result = 1;
    
    base %= mod;
    if (base == 0) return 0;   // edge case: 0^something mod m

    while (exp > 0) {
        if (exp & 1) {
            result = ((unsigned __int128)result * base) % mod;
        }
        base = ((unsigned __int128)base * base) % mod;
        exp >>= 1;
    }

    return result; 
}

void encryptFile(char* infile, char* publicKey, char* outname) {

  FILE* plaintext = fopen(infile, "r");
  FILE* encryptionKey = fopen(publicKey, "r");

  char encryptedname[256];
  snprintf(encryptedname, sizeof(encryptedname), "%s_secure.rsenc", outname);

  FILE* outfile = fopen(encryptedname, "w");

  if (plaintext == NULL || encryptionKey == NULL || outfile == NULL) {
    printf("Failed to open/create files\n");
  } else {

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

    int k = 0;
    while(fgets(line, sizeof(line), plaintext)) {
      //line[strcspn(line, "\n")] = 0;
    
      for (int i = 0; i < strlen(line); i++) {
        //printf("%"PRIu64"\n", n[k % BASE]);
        uint64_t value = (uint64_t) (unsigned char) line[i];
        uint64_t index = modular_pow((uint64_t) value, e[k % keys_read], n[k % keys_read]);
        //printf("Char %d: Encrypting %" PRIu64 " with e=%" PRIu64 ", n=%" PRIu64 " -> Result: %"PRIu64"\n", k, value, e[k % keys_read], n[k % keys_read], index);
        fprintf(outfile, "%" PRIu64 " ", index);
        k += 1;
      }
    }
    fclose(plaintext);
    fclose(encryptionKey);
    fclose(outfile);
  }
}

void decryptFile(char* infile, char* privateKey, char* outname, char* password) {

    FILE* cyphertext = fopen(infile, "r"), decryptionKey = fopen(privateKey, "r"), outfile = fopen(decryptedname, "w");
    int offset = offsetCreation(password);
    char decryptedname[256];
    snprintf(decryptedname, sizeof(decryptedname), "%s.txt", outname);


    if (cyphertext == NULL || decryptionKey == NULL || outfile == NULL) {
        printf("Failed to open/create files\n");
        if (cyphertext) fclose(cyphertext);
        if (decryptionKey) fclose(decryptionKey);
    }  else {
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
     rotate(d, offset, RIGHT);

    int k = 0;
    while(fgets(line, sizeof(line), cyphertext)) {
      char* token = strtok(line, " \n\r");
      while (token != NULL) {
        uint64_t val = strtoull(token, NULL, 10);
        //if (n[k % BASE] != 0) {
        uint64_t decrypted_val = modular_pow(val, d[k % keys_read], n[k % keys_read]);
        //printf("Char %d: Decrypting %" PRIu64 " with d=%" PRIu64 ", n=%" PRIu64 " -> Result: %"PRIu64"\n", k, val, d[k % keys_read], n[k % keys_read], decrypted_val);
        fputc((char)decrypted_val, outfile);
        k += 1;
        token = strtok(NULL, " \n\r");
      }
    }
    fclose(cyphertext);
    fclose(decryptionKey);
    fclose(outfile);
  }
}
