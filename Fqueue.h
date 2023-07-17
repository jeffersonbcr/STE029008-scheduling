#ifndef __FUNCTIONQUEUE_H__
#define __FUNCTIONQUEUE_H__

#include "fifo.h"
#include "LinkedList.h"
#include "defs.h"
#include "timer.h"

struct Event
{
    Microseconds time; 
    Microseconds release_time = Timer0::micros();
    void (*func)(void*);
    void * args;
    char priority; 
};

#if SCHED_TYPE == SCHED_FIFO
class FunctionQueue : public FIFO<Event *, 16>
{
    public:

        void run()
        {
            Event * next;
            __asm__ ("cli");
            while ( this->size() > 0)
            {
                this->dequeue(&next);
                __asm__ ("sei");
                next->func(next->args);
              
                __asm__ ("cli");
            }
            __asm__ ("sei");
        }
};
#elif SCHED_TYPE == SCHED_RMS
class FunctionQueue : public LinkedList<Event *, true, false, char> 
{
    private:

    public:

    void run()
    {
        Event  * next;
        __asm__ ("cli");
        while ( this->size() > 0)
        {
            next = this->remove_head();
            __asm__("sei");
            next->func(next->args);
            __asm__("cli");
        }
        __asm__("sei");
    }

};
#elif SCHED_TYPE == SCHED_EDD
class FunctionQueue : public LinkedList<Event *, true, false,Microseconds>
{
    private:

    public:

    void run()
    {
        Event  * next;
        __asm__ ("cli");
        while ( this->size() > 0)
        {
            next = this->remove_head();
            __asm__("sei");
            next->func(next->args);
            __asm__("cli");
        }
        __asm__("sei");
    }
};
#endif

#endif