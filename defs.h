#ifndef __DEFINICOES_H__
#define __DEFINICOES_H__

#define SCHED_FIFO 0
#define SCHED_RMS 1
#define SCHED_EDD 2
#define SCHED_TYPE SCHED_EDD

// Enable dynamic objects creation/destruction with C++
typedef unsigned int size_t;
typedef unsigned long long Microseconds; // 64-bits
void *operator new   (size_t objsize);
void  operator delete(void* obj);

#endif // __DEFINICOES_H__