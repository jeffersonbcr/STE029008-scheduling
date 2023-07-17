#include "defs.h"
#include "uart.h"
#include "timer.h"
#include "alarm.h"
#include <stdio.h>

Uart uart(Uart::UART_9600);
char strbuf[32];

FunctionQueue fqueue;
Timer0 timer;
Alarm alarm(&fqueue);

Event evt1, evt2;

const char * MSG1 = "Oi, tudo bem?\n";
void printMsg1(void * arg)
{
    alarm.schedule(&evt1);
    char * msg = (char *) arg;
    uart.puts(msg);
}

const char * MSG2 = "ping\n";
void printMsg2(void * arg)
{
    alarm.schedule(&evt2);
    char * msg = (char *) arg;
    uart.puts(msg);
}

void setup()
{
    uart.puts("setup\n");
    timer.registerObserver(&alarm);

    evt1.time = 1000000;
    evt1.func = printMsg1;
    evt1.args = (void*) MSG1;
    alarm.schedule(&evt1);

    evt2.time = 200000;
    evt2.func = printMsg2;
    evt2.args = (void*) MSG2;
    alarm.schedule(&evt2);
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