#include "../include/rsa.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

typedef enum {
CREATE_KEY,
ENCRYPt_FILE,
DECRYPT_FILE,
HELP
} Mode;

void displayHelp(void) {
  printf("Kevlar Encryption:\n\tSyntax goes here\n");
}

void displaySyntaxError(void) {
  printf("Invalid use of command\n");
}

int main(int argc, char* argv[]) {
  srand(time(NULL)); 

  int opt;
  while ((opt = getopt(argc, argv, "cedh")) != -1) {
    switch(opt) {
      case 'c':
        createKeys(argv[2]);
        break;
      case 'e':
        encryptFile(argv[2], argv[3], argv[4]);
        break;
      case 'd':
        decryptFile(argv[2], argv[3], argv[4]);
        break;
      case 'h':
        displayHelp();
        break;
      default:
        displaySyntaxError();
        break;
    } 
  }
}
