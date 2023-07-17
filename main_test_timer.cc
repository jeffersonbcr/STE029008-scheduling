// Arquivo: main.cc
// Autor: Arliones Hoeller, IFSC-SJE

#include <stdio.h>
#include "gpio_pin.h"
#include "uart.h"
#include "timer.h"

Uart uart(Uart::UART_9600);
Timer0 timer;

void setup()
{
    __asm__ ("sei");
    uart.puts("setup\n");
}

void busy_wait_delay(int times)
{
    while (times--)
    {
        unsigned long x = 0x7ffff;
        while(x--) __asm__ ("nop");
    }
}

void loop()
{
    timer.delay(1000000);
    uart.puts("loop\n");
}

int main()
{
    setup();
    while (true)
    {
        loop();
    }
}
