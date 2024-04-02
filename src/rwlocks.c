/*
COP4600 PA#2 Group 31
Evelyn Adams
Andrew Brink
Alicia Hassan
Jonah Henriksson

Reader-Writer locks struct definitions
*/

#include "rwlocks.h"

void rw_lock_init(RwLock *lock, void *data) {
  lock->num_ra = 0;
  lock->num_ww = 0;
  lock->wa = false;
  lock->data = data;
  Mutex_init(&lock->g);
  Cond_init(&lock->cond);
}

RGuard rw_lock_read(RwLock *lock) {
  Mutex_lock(&lock->g);
  while (lock->num_ww > 0 || lock->wa) {
    Cond_wait(&lock->cond, &lock->g);
  }
  lock->num_ra += 1;
  Mutex_unlock(&lock->g);
  return (RGuard){lock->data};
}

WGuard rw_lock_write(RwLock *lock) {
  Mutex_lock(&lock->g);
  lock->num_ww += 1;
  while (lock->num_ra > 0 || lock->wa) {
    Cond_wait(&lock->cond, &lock->g);
  }
  lock->num_ww -= 1;
  lock->wa = true;
  Mutex_unlock(&lock->g);
  return (WGuard){lock->data};
}

void rw_lock_drop_read(RwLock *lock, RGuard guard) {
  assert(guard.data ==
         lock->data); // Sanity check when multiple RwLocks are in play.
  Mutex_lock(&lock->g);
  lock->num_ra -= 1;
  if (lock->num_ra == 0) {
    Cond_signal(&lock->cond);
  }
  Mutex_unlock(&lock->g);
}

void rw_lock_drop_write(RwLock *lock, WGuard guard) {
  assert(guard.data ==
         lock->data); // Sanity check when multiple RwLocks are in play.
  Mutex_lock(&lock->g);
  lock->wa = false;
  Cond_signal(&lock->cond);
  Mutex_unlock(&lock->g);
}
