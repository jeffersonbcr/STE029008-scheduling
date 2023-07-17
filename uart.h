// Arquivo: uart.h
// Autor: Arliones Hoeller, IFSC-SJE

#ifndef __UART_H__
#define __UART_H__

#include "fifo.h"

class Uart
{
public:
    enum UART_Baudrate_t
    {
        UART_9600 = 103,
        UART_14400 = 68,
        UART_19200 = 51,
        UART_28800 = 34,
        UART_38400 = 25,

    };

    Uart(Uart::UART_Baudrate_t baud, int db = 8, int pr = 0, int sb = 1);
    ~Uart();

    void put(char c);
    void puts(const char *s);
    void puts(char *s);
    char get();
    static void rxc_handler();
    void txc_handler();
    static void udre_handler();

private:
    typedef FIFO<unsigned char, 128> Uart_FIFO;
    struct USART_Registers_t
    {
        volatile unsigned char UCSR0A;
        volatile unsigned char UCSR0B;
        volatile unsigned char UCSR0C;
        volatile unsigned char UCSReserved;
        volatile unsigned char UBRRL;
        volatile unsigned char UBRRH;
        volatile unsigned char udr;
    };
    static USART_Registers_t *uregs;

    static Uart_FIFO tx_fifo;
    static Uart_FIFO rx_fifo;
};

#endif