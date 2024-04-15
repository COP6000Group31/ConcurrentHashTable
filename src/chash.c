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
#include <common.h>
#include <pthread.h>
#include "hashdb.h"
#include "rwlocks.h"

#define MAX_LINE_LENGTH 100
#define COMMAND_LEN 10

int main() {
  FILE *inFile, *outFile;
  char line[MAX_LINE_LENGTH];
  char command[COMMAND_LEN];
  char name[NAME_LEN];
  uint32_t salary;
  int num_threads;

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

  //set up array of pthread structs
  pthread_t * pthreadArray;
  pthreadArray = malloc (sizeof(pthread_t) * num_threads);

  //create a hash table
  struct HashTable hashTable;
  hash_table_init(hashTable);

  //process the rest of the infile
  while (fgets(line, MAX_LINE_LENGTH, inFile) != NULL){
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
      if (record != NULL)
        fprintf(outFile, "%d,%s,%u\n", record->hash, record->name, record->salary);
      else
        fprintf(outFile, "No Record Found\n", );
    }
    else if (strcmp(command, "print") == 0){
      print_hash_table(hashTable->head, outFile);
    }
    else{
      perror("Unknown command recieved");
    }
  }

  // need final printing to be done
  //fprintf(outFile, "Number of lock acquisitions: %s\n", (hashTable->lock).acquisitionCtr);
  //fprintf(outFile, "Number of lock releases: %s\n", (hashTable->lock).releaseCtr);
  fprintf(outFile, "Final Table:\n", );
  print_hash_table(hashTable->head, outFile);

  //close all files
  fclose(inFile);
  fclose(outFile);
  return 0;

}
