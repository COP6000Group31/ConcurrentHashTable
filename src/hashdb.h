#ifndef HASHDB_H
#define HASHDB_H

#include <stdint.h>

#define NAME_LEN 50

/// Record in HashTable.
typedef struct HashRecord {
  uint32_t hash;           ///< Hash of name.
  char name[NAME_LEN];     ///< Name of employee.
  uint32_t salary;         ///< Annual salary of employee.
  struct HashRecord *next; ///< Next node in the list.
} HashRecord;

/// A concurrent hash table.
typedef struct HashTable {

} HashTable;

#endif // HASHDB_H
