#ifndef HASHDB_H
#define HASHDB_H

#include <stdint.h>
#include <string.h>

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

/// Initialize the hash table.
void hash_table_init(HashTable *ht);

/// Insert or update a record in the hash table.
void hash_table_insert(HashTable *ht, char *name, uint32_t salary);

/// Delete a record from the hash table.
void hash_table_delete(HashTable *ht, char *name);

/// Search the hash table for the key and return a pointer to the value.
HashRecord *hash_table_search(HashTable *ht, char *name);

/// Jenkins's one at a time hash function
uint32_t jenkins_one_at_a_time_hash(const uint8_t* key, size_t length);

#endif // HASHDB_H
