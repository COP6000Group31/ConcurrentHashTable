/*
COP4600 PA#2 Group 31
Evelyn Adams
Andrew Brink
Alicia Hassan
Jonah Henriksson

Main program that reads the commands.txt and
produces output to the console
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hashdb.h"

int main() {
  //Open input file
  inFile = fopen("commands.txt", "r");
  if (inFile == NULL) {
      perror("Error opening input file");
      return 1;
  }

  //Open Output File
  outFile = fopen("commands.txt", "r");
  if (outFile == NULL) {
      perror("Error opening input file");
      return 1;
  }



  //close all files
  fclose(inFile);
  fclose(outFile);
  return 0;
}
