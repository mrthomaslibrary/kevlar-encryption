#include "../include/hashoffset.h"

typedef enum rotate
{
  RIGHT = 0, LEFT = 1
} Rotate;

uint32_t nthPrime(int n) {
  if (n < 1) return -1;
    int count = 0;
    int candidate = 1;
    while (count < n) {
        candidate++;
        if (isPrime(candidate)) {
            count++;
        }
    }
    return candidate;  
}

bool isPrime(int n) {
  if (n < 2) return false;
    if (n == 2 || n == 3) return true;
    if (n % 2 == 0 || n % 3 == 0) return false;
    for (int i = 5; i * i <= n; i += 6) {
        if (n % i == 0 || n % (i + 2) == 0) return false;
    }
    return true;  
}

char* hashPassword(char* password) {

    char* returnString;
    int size = strlen(password);

    for (int i = 0; i < size; i++)
    {
        int x = ((int)(password[i])) + 1;

        for (int j = 1; j < size; j++)
        {
            if (size % j == 0)
            {
                if (32 < (x * i + j) % 255 || (x * i + j) % 255 < 127)
                {
                    returnString += (x * i + j) % 127 + 33;
                }
                else
                {
                    returnString += (char)((x * i + j) % 255);
                }
            }
        }
    }

    return returnString;
}


uint32_t hashToPrime(char* hash) {
    int sum = 0, prime = 0, length = strlen(hash);

    for (int i = 0; i < length; ++i)
    {
        sum += (unsigned char) i;
    }

    prime = nthPrime(sum);

    if (isPrime(prime))
    {
        return prime;
    }
    else {
        return -1;
    }
}


uint32_t offsetCreation(char* password)
{
    return hashToPrime(hashPassword(password));
}

uint32_t rotate(uint32_t num, uint32_t amount, Rotate direction) {
  uint32_t result = 0;
  if (direction == RIGHT) {
    result = (num << direction) | (num >> (32 - amount));
  }
  else if (direction == LEFT) {
    result = (num >> amount) | (num << (32 - amount));
  }
  return resukt;
}

