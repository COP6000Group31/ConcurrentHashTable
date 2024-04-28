#include "rwlocks.h"

void rwlock_init(rwlock_t *lock) {
  lock->num_ra = 0;
  lock->num_ww = 0;
  lock->wa = false;
  Mutex_init(&lock->g);
  Cond_init(&lock->cond);
}

void rwlock_acquire_readlock(rwlock_t *lock) {
  Mutex_lock(&lock->g);
  while (lock->num_ww > 0 || lock->wa) {
    Cond_wait(&lock->cond, &lock->g);
  }
  lock->num_ra += 1;
  Mutex_unlock(&lock->g);
}

void rwlock_release_readlock(rwlock_t *lock) {
  Mutex_lock(&lock->g);
  lock->num_ra -= 1;
  if (lock->num_ra == 0) {
    Cond_signal(&lock->cond);
  }
  Mutex_unlock(&lock->g);
}

void rwlock_acquire_writelock(rwlock_t *lock) {
  Mutex_lock(&lock->g);
  lock->num_ww += 1;
  while (lock->num_ra > 0 || lock->wa) {
    Cond_wait(&lock->cond, &lock->g);
  }
  lock->num_ww -= 1;
  lock->wa = true;
  Mutex_unlock(&lock->g);
}

void rwlock_release_writelock(rwlock_t *lock) {
  Mutex_lock(&lock->g);
  lock->wa = false;
  Cond_signal(&lock->cond);
  Mutex_unlock(&lock->g);
}

int read_loops;
int write_loops;
int counter = 0;

rwlock_t mutex;

void *reader(void *arg) {
  int i = 0;
  int local = 0;
  for (i = 0; i < read_loops; i++) {
    rwlock_acquire_readlock(&mutex);
    local = counter;
    rwlock_release_readlock(&mutex);
    printf("read %d\n", local);
  }
  printf("read done: %d\n", local);
  return NULL;
}

void *writer(void *arg) {
  int i = 0;
  for (i = 0; i < write_loops; i++) {
    rwlock_acquire_writelock(&mutex);
    counter++;
    rwlock_release_writelock(&mutex);
  }
  printf("write done\n");
  return NULL;
}
