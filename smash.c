#define _GNU_SOURCE
#include <stdio.h>    //Standard I/O functions and definitions
#include <stdlib.h>   //Standard library (includes exit function)
#include <string.h>  //String manipulation functions
#define MAXLINE 4096
#include "commands.h"

int main(int argc, char **argv) {
  setvbuf(stdout,NULL,_IONBF,0);
  char bfr[MAXLINE];
  fputs("$ ", stderr);
  
  // Loop read commands until EOF or error occurs...
  while(fgets(bfr, MAXLINE, stdin) != NULL) {
    bfr[strlen(bfr) - 1] = '\0'; // Replace newline with NULL
    executeCommand(bfr);
    fputs("$ ", stderr); // Output the first prompt
  }
  return 0;
}



