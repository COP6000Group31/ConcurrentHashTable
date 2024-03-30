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
#define COMMAND_LEN 10

int main() {
  FILE *inFile, *outFile;

  //Open input file
  inFile = fopen("commands.txt", "r");
  if (inFile == NULL) {
      perror("Error opening input file");
      return 1;
  }

  //Open Output File
  outFile = fopen("output.txt", "w");
  if (outFile == NULL) {
      perror("Error opening input file");
      return 1;
  }

  char line[MAX_LINE_LENGTH];
  char command[COMMAND_LEN];
  char name[NAME_LEN];
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
    // can remove thisn block if we dont use this anywhere later
    if (sscanf(line, "threads,%d,0", &num_threads) != 1) {
        perror("Invalid format in the first line");
        fclose(inFile);
        fclose(outFile);
        return 1;
    }

  //create a hash table
  //-> relpace with init function once we define it
  struct HashTable hashTable;

  //process the rest of the infile
  while (fgets(line, MAX_LINE_LENGTH, inFile)){
    sscanf(line, "%s %s %u", command, name, &salary);

    if(strcmp(command, "insert") == 0){
      fprintf(outFile, "INSERT,%s,%s\n", name, salary);
      hash_table_insert(&hashTable, &name, salary);
    }
    else if (strcmp(command, "delete") == 0){
      fprintf(outFile, "DELETE,%s\n", name);
      hash_table_delete(&hashTable, &name);
    }
    else if (strcmp(command, "search") == 0){
      fprintf(outFile, "SEARCH,%s\n", name);
      HashRecord* record = hash_table_search(&hashTable, &name)
      fprintf(output, "%d,%s,%u\n", record->hash, record->name, record->salary);
    }
    else if (strcmp(command, "print") == 0){

    }
  }




  //close all files
  fclose(inFile);
  fclose(outFile);
  return 0;
}
