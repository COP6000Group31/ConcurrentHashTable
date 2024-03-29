#ifndef RWLOCKS_H
#define RWLOCKS_H

#include <common_threads.h>
#include <stdbool.h>
#include <stdint.h>

/// A Read-Write lock for arbitrary data.
///
/// By providing guards for reads/writes, the interface is safe from readers
/// writing. It could be safer, but alas, C lacks generics and move semantics.
typedef struct RwLock {
  uint32_t num_ra;     //< Number of readers active.
  uint32_t num_ww;     //< Number of writers waiting.
  bool wa;             //< If there is an active writer.
  pthread_mutex_t g;   //< Mutex for critical area.
  pthread_cond_t cond; //< Condition variable for blocking threads.
  void *data;          //< Associated data of lock.
} RwLock;

/// A guard for readers.
typedef struct RGuard {
  void const *data; //< Read-only data.
} RGuard;

/// A guard for writers.
typedef struct WGuard {
  void *data; //< Read-Write data.
} WGuard;

/// Initialize the Read-Write lock.
void rw_lock_init(RwLock *lock, void *data);

/// Get read access to the lock.
RGuard rw_lock_read(RwLock *lock);

/// Get write access to the lock.
WGuard rw_lock_write(RwLock *lock);

/// Drop access to reader.
void rw_lock_drop_read(RwLock *lock, RGuard guard);

/// Drop access to writer.
void rw_lock_drop_write(RwLock *lock, WGuard guard);

#endif // RWLOCKS_H
