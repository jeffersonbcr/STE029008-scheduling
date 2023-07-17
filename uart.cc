#include "uart.h"

Uart::Uart_FIFO Uart::tx_fifo;
Uart::Uart_FIFO Uart::rx_fifo;
Uart::USART_Registers_t * Uart::uregs;

Uart::Uart(Uart::UART_Baudrate_t baud, int db, int pr , int sb )
{
    uregs = (USART_Registers_t *)0xc0;
    uregs->UBRRH = (unsigned char)((baud >> 8) & 0x0f);
    uregs->UBRRL = (unsigned char)(baud & 0x0ff);
    uregs->UCSR0A = 0;
    uregs->UCSR0B = (1 << 4) | (1 << 3);
    uregs->UCSR0C = (3 << 1);
}

Uart::~Uart()
{
}
extern "C"
{

    void __vector_18() __attribute__((signal));
    void __vector_19() __attribute__((signal));
}
void __vector_18()
{ 
    Uart::rxc_handler();
}

void __vector_19()
{ 
    Uart::udre_handler();
}

void Uart::rxc_handler()  
{
    __asm__("cli");
    rx_fifo.enqueue(uregs->udr);
    __asm__("sei");
}
void Uart::txc_handler() 
{
}
void Uart::udre_handler()  
{
    unsigned char data;
    if (tx_fifo.dequeue(&data) == Uart_FIFO::FIFO_SUCCESS)
    {
        uregs->udr = data;
    }
    else
    {
        uregs->UCSR0B &= ~(1 << 5);
    }
}

void Uart::puts(const char *s)
{
    while (*s != '\0')
    {
        put(*s++);
    }
}
void Uart::puts(char *s)
{
    puts((const char *)s);
}

void Uart::put(char s) 
{
    __asm__("cli");
    tx_fifo.enqueue(s);
    __asm__("sei");
    uregs->UCSR0B |= (1 << 5);
}
char Uart::get()
{
    unsigned char aux;

    if (rx_fifo.dequeue(&aux) == Uart_FIFO::FIFO_SUCCESS)
    {
        return aux;
    }
}