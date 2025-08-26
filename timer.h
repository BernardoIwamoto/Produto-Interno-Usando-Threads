#ifndef _TIMER_H_
#define _TIMER_H_

#include <sys/time.h>

/* Macro que mede o tempo atual em segundos com precisão de microssegundos */
#define GET_TIME(now) { \
   struct timeval t; \
   gettimeofday(&t, NULL); \
   now = t.tv_sec + t.tv_usec/1000000.0; \
}

#endif
