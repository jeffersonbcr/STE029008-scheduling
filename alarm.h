#ifndef __ALARM_H__
#define __ALARM_H__

#include "observer.h"
#include "timer.h"
#include "Fqueue.h"
#include "LinkedList.h"

class Alarm : public Observer
{
public:
   
    Alarm(FunctionQueue * _fqueue) :fqueue(_fqueue)
    {
        //No main
        //Quem é o fqueue que vai usado
        //registrar ele no timer
    }
    ~Alarm(){}
    //schedule para agendar um evento incluir na lista de eventos
    void schedule(Event * ev)
    {

        Microseconds t = ev->time - (Timer0::micros() - ev->release_time );
        __asm__ ("cli");
        #if SCHED_TYPE == SCHED_FIFO
            events.insert(event_, ev->time);
        #elif SCHED_TYPE == SCHED_RMS
            events.insert(ev, t);
        #elif SCHED_TYPE == SCHED_EDD
            events.insert(ev, ev->release_time + ev->time);
        #endif 
        __asm__ ("sei");
    }
    virtual void update(int val)
    {
        Microseconds rank = events.update_head_rank(val);
        if(rank == 0)
        {
            while(events.update_head_rank(0) == 0)
            {
                Event * ev = events.remove_head();
                #if SCHED_TYPE == SCHED_FIFO
                    fqueue->enqueue(ev);
                #elif SCHED_TYPE == SCHED_RMS
                    ev->release_time = Timer0::micros();
                    fqueue->insert(ev, ev->priority);
                #elif SCHED_TYPE == SCHED_EDD
                    ev->release_time = Timer0::micros(); //atualizar agora + deadline
                    fqueue->insert(ev, ev->release_time + ev->time);
                #endif    
                //atualizar release time
                rank = events.update_head_rank(0);
                //RMS
            }
        }

    }
private:
    FunctionQueue * fqueue;
    LinkedList<Event *,true,true,Microseconds> events;
};

#endif //_ALARM_H__