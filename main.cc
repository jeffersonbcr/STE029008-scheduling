// Arquivo: main.cc
// Autor: Arliones Hoeller, IFSC-SJE

#include <stdio.h>
#include "uart.h"
#include "adc.h"
#include "Fqueue.h"
#include "timer.h"
#include "LinkedList.h"
#include "defs.h"

Uart uart(Uart::UART_9600);
FunctionQueue fqueue;
LinkedList<int, true, true,int> list;
Timer0 timer = Timer0();
//void printMsg(void *arg)
//{
    //char *msg = (char *)arg;
    //uart.puts(msg);
    // fqueue.enqueue(evt);
//}
//const char *MSG = "Oi,tudo bem?";
/*
void setup()
{
    __asm__ ("sei");
    uart.puts("setup\n");
    Event evt;
    evt.time = 0;
    evt.func = printMsg;
    evt.args = (void *)MSG;
    fqueue.enqueue(evt);
}
*/
void setup()
{
    uart.puts("setup\n");
    list.insert(0,5);
    timer.delay(1000);
    list.insert(1,3);
    timer.delay(1000);
    list.insert(2,4);
    timer.delay(1000);
    list.insert(3,1);
    timer.delay(1000);
    
}
char strbuf[16];
void loop()
{
    while (list.size() > 0)
    {
        sprintf(strbuf, "Dequeued: %d\n", list.remove_head());
        uart.puts(strbuf); //3 1 2 0
        timer.delay(1000000);
    }
    
}

int main()
{
    setup();
    while (true)
    {
        loop();
    }
}
