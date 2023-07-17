#include "timer.h"

Microseconds Timer0::usec_counter = 0;
Timer0::Timer0_Regs_t * Timer0::regs = (Timer0::Timer0_Regs_t *) 0x44;
volatile unsigned char * Timer0::regs_timsk0 = (volatile unsigned char *) 0x6E;
LinkedList<Observer*,false,false> Timer0::observers;
extern "C"
{
    void __vector_16() __attribute__ ((signal));
}

void __vector_16()
{
    Timer0::timer0_isr_handler();
}