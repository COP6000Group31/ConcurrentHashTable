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
#include "hashdb.c"

#define MAX_LINE_LENGTH 100
#define COMMAND_LEN 10


int main() {
  FILE *inFile, *outFile;
 char filename[] = "commands.txt";
 char line[100];
 char *token;
 char *command, *name;
 uint32_t salary;
 int num_threads;
 int locks = 0;
 int releases = 0;

 struct HashTable hashTable;
 hash_table_init(&hashTable);


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

// Read the number of threads
    fgets(line, sizeof(line), inFile);
    sscanf(line, "threads,%d,", &num_threads);

    while (fgets(line, sizeof(line), inFile) != NULL) {
        // Tokenize the line
        token = strtok(line, ",");
        if (token != NULL) {
            command = token;
            if (strcmp(command, "insert") == 0) 
                {
                    // insert node into list
                    name = strtok(NULL, ",");
                    salary = atoi(strtok(NULL, ","));
                    fprintf(outFile, "INSERT,%s,%u\n", name, salary);
                    hash_table_insert(&hashTable, name, salary, outFile);
                } 
            else if (strcmp(command, "delete") == 0) 
                {
                    // get name and call delete function on appropriate node
                    name = strtok(NULL, ",");
                    fprintf(outFile, "DELETE,%s\n", name);
                    hash_table_delete(&hashTable, name, outFile);
                } 
            else if (strcmp(command, "search") == 0) 
                {
                    // search for name and output to fil
                    fprintf(outFile, "SEARCH,%s", name);
                    name = strtok(NULL, ",");
                    HashRecord* record = hash_table_search(&hashTable, name, outFile);
                    if (record != NULL)
                        fprintf(outFile, "%d,%s,%u\n", record->hash, record->name, record->salary);
                    else
                        fprintf(outFile, "No Record Found\n");
            
                } 
            else if (strcmp(command, "print") == 0) 
                {
                    //Print List
                    print_hash_table(hashTable.head, outFile);
                }
        }
    }
    fprintf(outFile, "\nNumber of lock acquisitions: %d\n", locks);
    fprintf(outFile,"Number of lock releases: %d\n", releases);
    print_hash_table(hashTable.head, outFile);
  //close all files
  fclose(inFile);
  fclose(outFile);
  return 0;

}
