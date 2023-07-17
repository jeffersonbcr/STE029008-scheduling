#include "defs.h"
#include "uart.h"
#include "adc.h"
#include "timer.h"
#include "alarm.h"
#include "fifo.h"
#include <stdio.h>

const Microseconds delay_time = 2000000;
Uart uart(Uart::UART_9600);

FunctionQueue fqueue;
Timer0 timer;
Alarm alarm(&fqueue);

Event evt1, evt2, evt3, evt4, evt5;

void evt1_func(void * arg)
{
    uart.puts("Task 0 - start\n");
    timer.delay(delay_time);
    //alarm.schedule(&evt1);
    uart.puts("Task 0 - end\n");
}

void evt2_func(void * arg)
{
    uart.puts("Task 1 - start\n");
    timer.delay(delay_time);
    //alarm.schedule(&evt2);
    uart.puts("Task 1 - end\n");
}

void evt3_func(void * arg)
{
    uart.puts("Task 2 - start\n");
    timer.delay(delay_time);
    //alarm.schedule(&evt3);
    uart.puts("Task 2 - end\n");
}

void evt4_func(void * arg)
{
    uart.puts("Task 3 - start\n");
    timer.delay(delay_time);
    // alarm.schedule(&evt4);
    uart.puts("Task 3 - end\n");
}

void evt5_func(void * arg)
{
    uart.puts("Task 4 - start\n");
    timer.delay(delay_time);
    //alarm.schedule(&evt5);
    uart.puts("Task 4 - end\n");
}

void setup()
{

    //Exemplo 1 - Earliest Due Date

    uart.puts("setup\n");
    timer.registerObserver(&alarm);
    
    uart.puts("Exemplo 1 - EDD\n");

    #if SCHED_TYPE == SCHED_EDD

        evt1.time = 3000000;
        evt1.func = evt1_func;
        evt1.args = (void*) 0;
        evt1.priority = 1;
        evt1.release_time = Timer0::micros();

        evt2.time = 10000000;
        evt2.func = evt2_func;
        evt2.args = (void*) 0;
        evt2.priority = 2;
        evt2.release_time = Timer0::micros();

        evt3.time = 7000000;
        evt3.func = evt3_func;
        evt3.args = (void*) 0;
        evt3.priority = 1;
        evt3.release_time = Timer0::micros();

        evt4.time = 8000000;
        evt4.func = evt4_func;
        evt4.args = (void*) 0;
        evt4.priority = 1;
        evt4.release_time = Timer0::micros();

        evt5.time = 5000000;
        evt5.func = evt5_func;
        evt5.args = (void*) 0;
        evt5.priority = 1;
        evt5.release_time = Timer0::micros();

        fqueue.insert(&evt1, evt1.release_time + evt1.time); //dealine = release + time
        fqueue.insert(&evt2, evt2.release_time + evt2.time);
        fqueue.insert(&evt3, evt3.release_time + evt3.time);
        fqueue.insert(&evt4, evt4.release_time + evt4.time);
        fqueue.insert(&evt5, evt5.release_time + evt5.time); //dealine = release + time

    #endif

    //Exemplo 2 - Earliest Due Date
    
    /*uart.puts("Exemplo 2 - EDD\n");

    #if SCHED_TYPE == SCHED_EDD
        evt1.time = 2000000;
        evt1.func = evt1_func;
        evt1.args = (void*) 0;
        evt1.priority = 1;
        evt1.release_time = Timer0::micros();

        evt2.time = 5000000;
        evt2.func = evt2_func;
        evt2.args = (void*) 0;
        evt2.priority = 2;
        evt2.release_time = Timer0::micros();

        evt3.time = 4000000;
        evt3.func = evt3_func;
        evt3.args = (void*) 0;
        evt3.priority = 1;
        evt3.release_time = Timer0::micros();

        evt4.time = 8000000;
        evt4.func = evt4_func;
        evt4.args = (void*) 0;
        evt4.priority = 1;
        evt4.release_time = Timer0::micros();

        evt5.time = 6000000;
        evt5.func = evt5_func;
        evt5.args = (void*) 0;
        evt5.priority = 1;
        evt5.release_time = Timer0::micros();

        fqueue.insert(&evt1, evt1.release_time + evt1.time); //dealine = release + time
        fqueue.insert(&evt2, evt2.release_time + evt2.time);
        fqueue.insert(&evt3, evt3.release_time + evt3.time);
        fqueue.insert(&evt4, evt4.release_time + evt4.time);
        fqueue.insert(&evt5, evt5.release_time + evt5.time); //dealine = release + time
    #endif */
}

void loop()
{
    fqueue.run();
}

int main()
{
    setup();

    while (true)
    {
        loop();
    }
}
