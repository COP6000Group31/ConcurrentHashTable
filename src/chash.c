/*
COP4600 PA#2 Group 31
Evelyn Adams
Andrew Brink
Alicia Hassan
Jonah Henriksson

Main program that reads the commands.txt and
produces output to the console
*/
#include "hashdb.h"

#define MAX_LINE_LENGTH 100
#define COMMAND_LEN 10
#define MAX_NAME_LEN 50

typedef struct ThreadArg {
  HashTable *hashTable;
  FILE *outFile;
  char command[COMMAND_LEN];
  char name[MAX_NAME_LEN];
  uint32_t salary;
} ThreadArg;

int num_locks = 0;
int num_releases = 0;

void *process_command(void *arg) {
  ThreadArg *threadArg = (ThreadArg *)arg;
  if (strcmp(threadArg->command, "insert") == 0) {
    hash_table_insert(threadArg->hashTable, threadArg->name, threadArg->salary,
                      threadArg->outFile);
  } else if (strcmp(threadArg->command, "delete") == 0) {
    hash_table_delete(threadArg->hashTable, threadArg->name,
                      threadArg->outFile);
  } else if (strcmp(threadArg->command, "search") == 0) {
    hash_table_search(threadArg->hashTable, threadArg->name,
                      threadArg->outFile);
  } else if (strcmp(threadArg->command, "print") == 0) {
    print_hash_table(threadArg->hashTable, threadArg->outFile);
  }
  return NULL;
}

int main() {
  FILE *inFile = NULL;
  FILE *outFile = NULL;
  char filename[] = "commands.txt";
  char line[MAX_LINE_LENGTH];
  int num_threads = 0;

  HashTable hashTable;
  hash_table_init(&hashTable);

  // Open input file
  inFile = fopen(filename, "re");
  if (inFile == NULL) {
    perror("Error opening input file");
    return 1;
  }

  // Open Output File
  outFile = fopen("output.txt", "we");
  if (outFile == NULL) {
    perror("Error opening output file");
    return 1;
  }

  // Read the number of threads
  fgets(line, sizeof(line), inFile);
  sscanf(line, "threads,%d,", &num_threads);
  fprintf(outFile, "Running %d threads\n", num_threads);

  pthread_t *threads = calloc(num_threads, sizeof(pthread_t));
  ThreadArg *threadArgs = calloc(num_threads, sizeof(ThreadArg));

  for (int i = 0; i < num_threads; i++) {
    if (fgets(line, sizeof(line), inFile) == NULL) {
      break;
    }
    char *token = strtok(line, ",");
    strcpy(threadArgs[i].command, token);

    if (strcmp(token, "insert") == 0 || strcmp(token, "delete") == 0 ||
        strcmp(token, "search") == 0) {
      strcpy(threadArgs[i].name, strtok(NULL, ","));
      threadArgs[i].salary =
          (strcmp(token, "insert") == 0) ? atoi(strtok(NULL, "\n")) : 0;
    }

    threadArgs[i].hashTable = &hashTable;
    threadArgs[i].outFile = outFile;

    pthread_create(&threads[i], NULL, process_command, &threadArgs[i]);
  }

  for (int i = 0; i < num_threads; i++) {
    pthread_join(threads[i], NULL);
  }

  // Final Print
  fprintf(outFile, "\nFinal Hash Table\n");
  fprintf(outFile, "Number of lock acquisitions: %d\n", num_locks);
  fprintf(outFile, "Number of lock releases: %d\n", num_releases);
  print_hash_table(&hashTable, outFile);

  //   Close all files
  fclose(inFile);
  fclose(outFile);
  free(threads);
  free(threadArgs);
  return 0;
}
