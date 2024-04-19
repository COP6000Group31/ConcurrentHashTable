#ifndef RWLOCK_H
#define RWLOCK_H

#include <common_threads.h>
#include <stdio.h>

// Define the rwlock_t structure
typedef struct rwlock_t {
  sem_t writelock;
  sem_t lock;
  int readers;
} rwlock_t;

// Function prototypes for initializing and managing read-write locks
void rwlock_init(rwlock_t *lock);
void rwlock_acquire_readlock(rwlock_t *lock);
void rwlock_release_readlock(rwlock_t *lock);
void rwlock_acquire_writelock(rwlock_t *lock);
void rwlock_release_writelock(rwlock_t *lock);

#endif // RWLOCK_H
