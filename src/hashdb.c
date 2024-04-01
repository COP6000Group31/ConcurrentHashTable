/*
COP4600 PA#2 Group 31
Evelyn Adams
Andrew Brink
Alicia Hassan
Jonah Henriksson

Concurrent Hash Table struct definitions
*/
#include "hashdb.h"


// Delete a record from the hash table.
void hash_table_delete(HashTable *ht, char *name){
  // search for the record
  HashRecord* delRec = hash_table_search(&hashTable, &name)

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
  return;
}

/* given the head of the hash table, print the entire contents
   of the list to the output file */
void print_hash_table(HashRecord *cur, FILE *outFile){
  while (cur != NULL) {
    fprintf(outFile, "%u,%s,%u\n", cur->hash, cur->name, cur->salary);
    cur = cur->next;
  }
}
