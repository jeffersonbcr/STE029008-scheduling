#ifndef __TIMER_H__
#define __TIMER_H__

#include "LinkedList.h"
#include "observer.h"
#include "defs.h"

class Timer0
{
public:
    //typedef unsigned long long Microseconds; // 64-bits
    static const unsigned char TOP = 125;
    static const unsigned char MAX = 255;
    static const unsigned char TIMER_BASE = MAX - TOP + 1;
    static const unsigned int TIMER_RESOLUTION = 2000;

    Timer0()
    {
        regs->tccr0a = 0x00;
        regs->tccr0b = 0x04;
        regs->tcnt0 = TIMER_BASE;
        *regs_timsk0 = 0x01;
    }
    void registerObserver(Observer * obs)
    {
        observers.insert(obs);
    }
    static Microseconds micros() { return usec_counter; }

    static void timer0_isr_handler()
    {
        regs->tcnt0 = TIMER_BASE;
        usec_counter += TIMER_RESOLUTION;
        Observer *obs = 0;
        for (int i = 0; i < observers.size(); i++)
        {
            obs = observers.get(i);
            obs->update(TIMER_RESOLUTION);
        }
    }

    void delay(Microseconds d)
    {
        Microseconds end = micros() + d;
        while (micros() < end);
    }

private:
    struct Timer0_Regs_t
    {
        volatile unsigned char tccr0a;
        volatile unsigned char tccr0b;
        volatile unsigned char tcnt0;
    };
    static volatile unsigned char * regs_timsk0;
    static Timer0_Regs_t * regs;
    static Microseconds usec_counter;

    static LinkedList<Observer*,false,false> observers;
};

#endif