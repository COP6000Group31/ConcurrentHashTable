/*
COP4600 PA#2 Group 31
Evelyn Adams
Andrew Brink
Alicia Hassan
Jonah Henriksson

Concurrent Hash Table implementation,
including Jenkins function and all linked list operations
*/
#ifndef HASHDB_H
#define HASHDB_H

#include <stdint.h>
#include <stdio.h>

// Include semaphore-based locking definitions
#include "common.h"
#include "common_threads.h"
#include "rwlocks.h"

#define NAME_LEN 50

/// Record in HashTable.
typedef struct HashRecord {
  uint32_t hash;
  char name[NAME_LEN]; // Adjust as needed for actual name length
  uint32_t salary;
  struct HashRecord *next;
  struct HashRecord *prev;
} HashRecord;

/// A concurrent hash table.
typedef struct HashTable {
  HashRecord *head;
  rwlock_t lock;
} HashTable;

/// Initialize the hash table.
void hash_table_init(HashTable *ht);

/// Insert or update a record in the hash table.
void hash_table_insert(HashTable *ht, char *name, uint32_t salary,
                       FILE *outFile);

/// Delete a record from the hash table.
void hash_table_delete(HashTable *ht, char *name, FILE *outFile);

/// Search the hash table for the key and return a pointer to the value.
void hash_table_search(HashTable *ht, char *name, FILE *outFile);

/// Print the entire hash table to the output file.
void print_hash_table(HashTable *ht, FILE *outFile);

#endif // HASHDB_H
