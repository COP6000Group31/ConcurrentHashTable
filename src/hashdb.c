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

/// Initialize the hash table.
void hash_table_init(HashTable *ht){
  ht->head = NULL;
  rw_lock_init(&ht->lock, &ht->head);

  return;
}

// Delete a record from the hash table.
void hash_table_delete(HashTable *ht, char *name){
  //aquire write lock

  // search for the record
  HashRecord *delRec = unlocked_hash_table_search(ht, name);

  // base case
  if (*delRec == NULL)
    return;

  // Change next only if node to be deleted is NOT the last node
  if (delRec->next != NULL)
    delRec->next->previous = del->previous;

  // Change next only if node to be deleted is NOT the last node
  if (delRec->previous != NULL)
    delRec->previous->next = delRec->previous;

  // Free the memory of the deleted record
  free(delRec);

  //free the lock

  return;

// Jenkins one at a time hash function
uint32_t jenkins_one_at_a_time_hash(const char *key, size_t length) {
  size_t i = 0;
  uint32_t hash = 0;
  while (i != length) {
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
void print_hash_table(HashRecord *cur, FILE *outFile) {
  while (cur != NULL) {
    fprintf(outFile, "%u,%s,%u\n", cur->hash, cur->name, cur->salary);
    cur = cur->next;
  }
  return;
}

HashRecord *unlocked_hash_table_search(HashTable *ht, char *name){
  // compute the search key's hash value
  uint32_t hash = jenkins_one_at_a_time_hash(name, strlen(name));

  //start at head of list
  HashRecord *current = ht->head;

  // search the linked list for hash
  while (current != NULL) {
    // if key is found, stop looking
    if (current->hash == hash) {
      break;
}

HashRecord *hash_table_search(HashTable *ht, char *name) {

  // acquire the read lock of the linked list
  // ht->rg = rw_lock_read(ht->lock);
  HashRecord *result = unlocked_hash_table_search(ht, name)
  // release the read lock
  // rw_lock_drop_write(ht->lock, ht->wg);

  return result;
  // release the read lock
  // rw_lock_drop_write(ht->lock, ht->wg);
}

void hash_table_insert(HashTable *ht, char *name, uint32_t salary) {
  int len = strlen(name);
  uint32_t hash = jenkins_one_at_a_time_hash(name, len);

  // Search for the key in the linked list
  HashRecord *current = ht->head;
  while (current != NULL) {
    if (current->hash == hash) {
      current->salary = salary;
      return;
    }
    current = current->next;
  }

  // Create a new node for the key-data pair
  HashRecord *newRecord = (HashRecord *)malloc(sizeof(HashRecord));
  if (newRecord == NULL) {
    printf("Memory allocation failed.\n");
    return;
  }
  newRecord->hash = hash;
  strcpy(newRecord->name, name);
  newRecord->salary = salary;
  newRecord->next = NULL;
  newRecord->prev = NULL;

  // Insert the new node at the beginning of the linked list
  newRecord->next = ht->head;
  if (ht->head != NULL) {
    ht->head->prev = newRecord;
  }
  ht->head = newRecord;
}
