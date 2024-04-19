#ifndef __common_h__
#define __common_h__

#include <assert.h>
#include <stddef.h>
#include <sys/stat.h>
#include <sys/time.h>

static inline double GetTime()
{
  struct timeval t;
  int rc = gettimeofday(&t, NULL);
  assert(rc == 0);
  return (double)t.tv_sec + (double)t.tv_usec / 1e6;
}

static inline void Spin(int howlong)
{
  double t = GetTime();
  while ((GetTime() - t) < (double)howlong)
    ; // do nothing in loop
}

#endif // __common_h__
