#include "hashdb.h"
#include "rwlocks.h"
#include <common.h>
#include <stdio.h>

RwLock lock;

typedef struct ThreadData {
  int new_data;
} ThreadData;

void *normalThread(void *arg) {
  ThreadData *td = arg;

  Spin(td->new_data);

  WGuard write = rw_lock_write(&lock);

  *(int *)write.data = td->new_data;

  printf("%d\n", *(int *)write.data);

  rw_lock_drop_write(&lock, write);
  return NULL;
}

void *readThread(void *arg) {
  Spin(8);
  RGuard read = rw_lock_read(&lock);

  int data = *(int const *)read.data;

  printf("%d\n", data);

  rw_lock_drop_read(&lock, read);
  return NULL;
}

int main() {
  int data = 0;

  rw_lock_init(&lock, &data);

  pthread_t t0;
  pthread_t t1;
  pthread_t t2;
  pthread_t t3;
  pthread_t t4;
  Pthread_create(&t0, NULL, normalThread, &(ThreadData){1});
  Pthread_create(&t1, NULL, normalThread, &(ThreadData){5});
  Pthread_create(&t2, NULL, normalThread, &(ThreadData){3});
  Pthread_create(&t3, NULL, normalThread, &(ThreadData){10});
  Pthread_create(&t4, NULL, readThread, NULL);

  Pthread_join(t0, NULL);
  Pthread_join(t1, NULL);
  Pthread_join(t2, NULL);
  Pthread_join(t3, NULL);
  Pthread_join(t4, NULL);

  return 0;
}
