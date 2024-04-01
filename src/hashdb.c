#include "hashdb.h"

uint32_t jenkins_one_at_a_time_hash(const uint8_t* key, size_t length) {
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

HashRecord *hash_table_search(HashTable *ht, char *name) {
    // compute name's hash value
    uint32_t hash = jenkins_one_at_a_time_hash(name, strlen(name));

    // locate the node based on the hash value
    HashRecord *current = ht->head;

    // acquire the read lock of the linked list
    ht->rg = rw_lock_read(ht->lock);

    // search the linked list for name
    while (current != NULL) {
        // if name is found, return it
        if (current->hash == hash) {
          // release the read lock
          rw_lock_drop_write(ht->lock, ht->wg);
          return current;
        }

        current = current->next;
    }

    // release the read lock
    rw_lock_drop_write(ht->lock, ht->wg);
  
    return NULL;   
}

/*
This function searches for a key-data pair in the hash table 
and returns the value, if it exists. To search for a key-data pair, 
the function first computes the hash value of the key 
and locates the corresponding node. Then, 
it acquires the read lock that protects the list 
and searches the linked list for the key. 
If the key is found, it returns the value. Otherwise, it returns NULL. 
Finally, it releases the read lock and returns. The caller should then 
print the record or "No Record Found" if the return is NULL.
*/
