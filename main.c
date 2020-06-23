/****************************************************************************
This piece of code (main.c) pretty much just handles all of the CLI arguments
and envokes all of the other functions that's needed to run this code.
Code by: GRIM-OPS
License:
                      GNU GENERAL PUBLIC LICENSE
                       Version 3, 29 June 2007
****************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "file/fileRW.h"
#include "aes/aes/encrypt.h"
#include "aes/invaes/decrypt.h"
#include "input/getArgs.h"

int main(int argc, char *argv[])
{
  int argLoc = 0;
  
  if(argc == 1)
  {
    printf("-h or --help\t\tDisplay help menu\n");
    printf("-m or --mode\t\tSets mode: [e]ncrypt, [d]ecrypt\n");
    printf("-f or --file\t\tSets file input: <filepath>\n");
    printf("-k or --key \t\tSets path to key: <filepath> Needs file to hold 128bit(16 byte) sequence\n");
    printf("-g or --gen \t\tGenerates 128 bit key and stores in key.txt file\n");
    return 0;
  }
  else if(getArgs('h', "--help", argc, argv))
  {
    printf("-h or --help\t\tDisplay help menu\n");
    printf("-m or --mode\t\tSets mode: [e]ncrypt, [d]ecrypt\n");
    printf("-f or --file\t\tSets file input: <filepath>\n");
    printf("-k or --key \t\tSets path to key: <filepath> Needs file to hold 128bit(16 byte) sequence\n");
    printf("-g or --gen \t\tGenerates 128 bit key and stores in key.txt file\n");
    return 0;
  }

  if(getArgs('g', "--gen", argc, argv))  // Generate a 128 bit key
  {
    unsigned char genKey[16];
    srand(time(0));
    printf("[+] Generating key...\n");
    for(int i = 0; i < 16; i++)
    {
      genKey[i] = rand() % 256;
    }
    writeFile("key.txt", 16, &genKey[0]);
    printf("[+] Generated!\n");
    return 0;
  }



  unsigned char key[4][4];
  argLoc = getArgs('k', "--key", argc, argv);
  if(argLoc)                                 // user sets where key path
  {
    if(argLoc + 1 >= argc)
    {
      fprintf(stderr, "[!] No key option found\n");
      return 1;
    }
    printf("[+] Getting key...\n");
    size_t size;
    unsigned char *pKey = readFile(argv[argLoc + 1], &size);
    if(size != 16)
    {
      fprintf(stderr, "[!]key size is too big or too small\n");
      return 1;
    }
    int i = 0;
    for(int row = 0; row < 4; row++)
    {
      for(int column = 0; column < 4; column++)
      {
        key[row][column] = *(pKey + i);
	i++;
      } 
    }
    printf("[+] Key found!\n");
  }
  else
  {
    fprintf(stderr, "[!] Need key file to operate\n");
    return 1;
  }



  unsigned char *filePath;
  argLoc = getArgs('f', "--file", argc, argv);
  if(argLoc)                                     // user sets file path
  {
    if(argLoc + 1 >= argc)
    {
      fprintf(stderr, "[!] Not a valid mode\n");
      return 1;
    }
    filePath = argv[argLoc + 1];
    printf("[+] File Path: %s\n", filePath);
  }
  else
  {
    fprintf(stderr, "[!] Need the file path to operate\n");
  }



  argLoc = getArgs('m', "--mode", argc, argv);
  if(argLoc)                                                      //This is the mode, either decrypt or encrypt
  {
    if(argLoc + 1 >= argc)
    {
      fprintf(stderr, "[!] Mode needs an option\n");
      return 1;
    }
    if(!strcmp(argv[argLoc + 1],"e")) //encrypt
    {
      printf("[+] Mode: Encrypt\n");
      size_t size;
      unsigned char *str = readFile(filePath, &size);
      printf("[+] Encrypting...\n");
      unsigned char *cipher = encrypt(str, key, size, &size);
      printf("[+] Encrypted!\n");
      free(str);
      printf("[+] Writing over file...\n");
      writeFile(filePath, size, cipher);
      printf("[+] File written!\n");
    }
    else if(!strcmp(argv[argLoc + 1],"d"))  //decrypt
    {
      printf("[+] Mode: Decrypt\n");
      size_t size;
      unsigned char *str = readFile(filePath, &size);
      printf("[+] Decrypting...\n");
      unsigned char *cipher = decrypt(str, key, size, &size);
      printf("[+] Decrypted!\n");
      free(str);
      printf("[+] Writing over file...\n");
      writeFile(filePath, size, cipher);
      printf("[+] File written!\n");
    }
    else
    {
      fprintf(stderr, "[!] %s is not a valid mode\n", argv[argLoc + 1]);
      return 1;
    }
  }
  else
  {
    fprintf(stderr, "[!] Need mode to operate\n");
    return 1;
  }

return 0;
}
