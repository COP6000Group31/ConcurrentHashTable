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

#define MAX_LINE_LENGTH 100

int main() {
  FILE *inFile, *outFile;

  //Open input file
  inFile = fopen("commands.txt", "r");
  if (inFile == NULL) {
      perror("Error opening input file");
      return 1;
  }

  //Open Output File
  outFile = fopen("commands.txt", "w");
  if (outFile == NULL) {
      perror("Error opening input file");
      return 1;
  }

  char line[MAX_LINE_LENGTH];
  char command[10];
  char name[50];
  uint32_t salary;
  int num_threads;

  //process line 1 of input file
  if (fgets(line, MAX_LINE_LENGTH, inFile) == NULL) {
        perror("Error reading the number of threads");
        fclose(inFile);
        fclose(outFile);
        return 1;
    }

    //Parse line 1 to get the number of threads
    if (sscanf(line, "threads,%d,0", &num_threads) != 1) {
        perror("Invalid format in the first line");
        fclose(inFile);
        fclose(outFile);
        return 1;
    }

  //create empty hash table
  //-> relpace with init function once we define the struct
  HashTable hashTable;

  //process the rest of the infile
  while (fgets(line, MAX_LINE_LENGTH, inFile)){
    sscanf(line, "%s %s %u", command, name, &salary);  //add check that reads correctly

    if(strcmp(command, "insert") == 0){
      hash_table_insert(&hashTable, &name, salary);
    }
    else if (strcmp(command, "delete") == 0){
      hash_table_delete(&hashTable, &name);
    }
    else if (strcmp(command, "search") == 0){
      HashRecord record = hash_table_search(&hashTable, &name)
    }
    else if (strcmp(command, "print") == 0){

    }
  }




  //close all files
  fclose(inFile);
  fclose(outFile);
  return 0;
}
