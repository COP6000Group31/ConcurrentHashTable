#ifndef RWLOCK_H
#define RWLOCK_H

#include <common_threads.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>

// Define the rwlock_t structure
typedef struct rwlock_t {
  uint32_t num_ra;     ///< Number of readers active.
  uint32_t num_ww;     ///< Number of writers waiting.
  bool wa;             ///< If there is an active writer.
  pthread_mutex_t g;   ///< Mutex for critical area.
  pthread_cond_t cond; ///< Condition variable for blocking threads.
} rwlock_t;

// Function prototypes for initializing and managing read-write locks
void rwlock_init(rwlock_t *lock);
void rwlock_acquire_readlock(rwlock_t *lock);
void rwlock_release_readlock(rwlock_t *lock);
void rwlock_acquire_writelock(rwlock_t *lock);
void rwlock_release_writelock(rwlock_t *lock);

#endif // RWLOCK_H
