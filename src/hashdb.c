/*
COP4600 PA#2 Group 31
Evelyn Adams
Andrew Brink
Alicia Hassan
Jonah Henriksson

Concurrent Hash Table struct definitions
*/
#include "hashdb.h"
#include <stdint.h>
#include <stdlib.h>

void hash_table_init(HashTable *ht)
{
  ht->head = NULL;
  return;
}

// Jenkins one at a time hash function
uint32_t jenkins_one_at_a_time_hash(const char *key, size_t length)
{
  size_t i = 0;
  uint32_t hash = 0;
  while (i != length)
  {
    hash += key[i++];
    hash += hash << 10;
    hash ^= hash >> 6;
  }
  hash += hash << 3;
  hash ^= hash >> 11;
  hash += hash << 15;
  return hash;
}

/* given the head of the hash table, print the entire contents
   of the list to the output file */
void print_hash_table(HashRecord *cur, FILE *outFile)
{
  fprintf(outFile, "READ LOCK ACQUIRED\n");

  while (cur != NULL)
  {
    fprintf(outFile, "%u,%s,%u\n", cur->hash, cur->name, cur->salary);
    cur = cur->next;
  }
  fprintf(outFile, "READ LOCK RELEASED\n");
  return;
}

void hash_table_insert(HashTable *ht, char *name, uint32_t salary, FILE *outFile)
{
  int len = strlen(name);
  uint32_t hash = jenkins_one_at_a_time_hash(name, len);

  fprintf(outFile, "INSERT,%u,%s,%u\n", hash, name, salary);
  fprintf(outFile, "WRITE LOCK ACQUIRED\n");

  // Search for the key in the linked list
  HashRecord *current = ht->head;
  while (current != NULL)
  {
    if (current->hash == hash)
    {
      current->salary = salary;
      return;
    }
    current = current->next;
  }

  // Create a new node for the key-data pair
  HashRecord *newRecord = (HashRecord *)malloc(sizeof(HashRecord));
  if (newRecord == NULL)
  {
    printf("Memory allocation failed.\n");
    return;
  }
  newRecord->hash = hash;
  strcpy(newRecord->name, name);
  newRecord->salary = salary;
  newRecord->next = NULL;
  newRecord->prev = NULL;

  // insert in numerical order
  if (ht->head == NULL || (ht)->head->hash >= hash)
  {
    newRecord->next = ht->head;
    if (ht->head != NULL)
    {
      ht->head->prev = newRecord;
    }
    ht->head = newRecord;
  }
  else
  {
    HashRecord *current = ht->head;
    while (current->next != NULL && current->next->hash < hash)
    {
      current = current->next;
    }
    // Insert the new record
    newRecord->next = current->next;
    if (current->next != NULL)
    {
      current->next->prev = newRecord;
    }
    current->next = newRecord;
    newRecord->prev = current;
  }
  fprintf(outFile, "WRITE LOCK RELEASED\n");
}

HashRecord *hash_table_search(HashTable *ht, char *name, FILE *outFile)
{

  // compute the search key's hash value
  uint32_t hash = jenkins_one_at_a_time_hash(name, strlen(name));
  fprintf(outFile, "READ LOCK ACQUIRED\n");
  // start at head of list
  HashRecord *current = ht->head;

  // search the linked list for hash
  while (current != NULL)
  {
    // if key is found, stop looking
    if (current->hash == hash)
    {
      return current;
    }

    current = current->next;
  }
  fprintf(outFile, "READ LOCK RELEASED\n");
  return NULL;
}

void hash_table_delete(HashTable *ht, char *name, FILE *outFile)
{
  // aquire write lock
  //  search for the record
  int length = strlen(name);
  uint32_t hash = jenkins_one_at_a_time_hash(name, length);

  fprintf(outFile, "WRITE LOCK ACQUIRED\n");

  HashRecord *current = ht->head;

  // search the linked list for hash
  while (current != NULL)
  {
    // if key is found, stop looking
    if (current->hash == hash)
    {
      if (current->prev != NULL)
      {
        current->prev->next = current->next;
      }
      else
      {
        ht->head = current->next;
      }
      if (current->next != NULL)
      {
        current->next->prev = current->prev;
      }
      free(current);
      return;
    }

    current = current->next;
  }
  fprintf(outFile, "WRITE LOCK RELEASED\n");
  return;
}
