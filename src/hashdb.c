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
  rwlock_init(&ht->lock);
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
void print_hash_table(HashTable *ht, FILE *outFile)
{

  rwlock_acquire_readlock(&ht->lock);
  fprintf(outFile, "READ LOCK ACQUIRED\n");

  HashRecord *cur = ht->head;
  while (cur != NULL)
  {
    fprintf(outFile, "%u,%s,%u\n", cur->hash, cur->name, cur->salary);
    cur = cur->next;
  }

  rwlock_release_readlock(&ht->lock);
  fprintf(outFile, "READ LOCK RELEASED\n");
}

void hash_table_insert(HashTable *ht, char *name, uint32_t salary, FILE *outFile)
{
  int len = strlen(name);
  uint32_t hash = jenkins_one_at_a_time_hash(name, len);

  fprintf(outFile, "INSERT,%u,%s,%u\n", hash, name, salary);

  rwlock_acquire_writelock(&ht->lock);
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
  rwlock_release_writelock(&ht->lock);
  fprintf(outFile, "WRITE LOCK RELEASED\n");
}

void hash_table_search(HashTable *ht, char *name, FILE *outFile)
{
  uint32_t hash = jenkins_one_at_a_time_hash(name, strlen(name));
  rwlock_acquire_readlock(&ht->lock);
  fprintf(outFile, "READ LOCK ACQUIRED\n");

  HashRecord *current = ht->head;
  while (current != NULL)
  {
    if (current->hash == hash && strcmp(current->name, name) == 0)
    {
      fprintf(outFile, "%u,%s,%u\n", current->hash, current->name, current->salary);
      break;
    }
    current = current->next;
  }

  rwlock_release_readlock(&ht->lock);
  fprintf(outFile, "READ LOCK RELEASED\n");
}

void hash_table_delete(HashTable *ht, char *name, FILE *outFile)
{
  uint32_t hash = jenkins_one_at_a_time_hash(name, strlen(name));
  rwlock_acquire_writelock(&ht->lock);
  fprintf(outFile, "WRITE LOCK ACQUIRED\n");

  HashRecord *current = ht->head;
  HashRecord *prev = NULL;
  while (current != NULL)
  {
    if (current->hash == hash && strcmp(current->name, name) == 0)
    {
      if (prev != NULL)
      {
        prev->next = current->next;
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
      break;
    }
    prev = current;
    current = current->next;
  }

  rwlock_release_writelock(&ht->lock);
  fprintf(outFile, "WRITE LOCK RELEASED\n");
}
