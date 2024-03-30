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
    return

  // Change next only if node to be deleted is NOT the last node
  if (delRec != NULL)
    delRec->next->previous = del->previous;

  // Change next only if node to be deleted is NOT the last node
    delRec->previous->next = delRec->previous;

  // Free the memory of the deleted record 
  free(delRec);
  return;
}
