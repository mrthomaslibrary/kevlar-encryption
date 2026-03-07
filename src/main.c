#include "../include/rsa.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

//Help documentation command
void displayHelp(void) {
  printf("Kevlar Encryption:\n");
  printf("\tCreate Keys\t|\t-c <key-names>\n");
  printf("\tEncrypt File\t|\t-e <plain-text> <public-key> <outfile-name>\n");
  printf("\tDecrypt File\t|\t-d <encrypted-file> <private-key> <outfile-name>\n");
  printf("\tHelp\t\t|\t-h Prints This Message\n");
}

//Syntax error response
void displaySyntaxError(void) {
  printf("Invalid use of command\n");
}

//Main function runs program and interprets flags
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
