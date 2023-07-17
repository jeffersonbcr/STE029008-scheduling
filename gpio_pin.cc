#include "gpio_pin.h"
 
//atributos estaticos precisam estar declarados por linkagem para o programa em c
GPIO_Pin::handlerFunc GPIO_Pin::handlers[2]; //ponto de linkagem do handler
volatile unsigned char * GPIO_Pin::eicra = (volatile unsigned char *) 0x69;
volatile unsigned char * GPIO_Pin::eimsk = (volatile unsigned char *) 0x3d;
extern "C" //definindo para gcc o assembly de C o vector receber o attribute. Linkagem para ponteiros de memória.
{
   void __vector_1() __attribute__ ((signal));
   void __vector_2() __attribute__ ((signal));
}
 
void __vector1()
{
   //chamar o handler do INT0
   GPIO_Pin::handlers[0]();
}
 
void __vector2()
{
   //chamar o handler do INT1
   GPIO_Pin::handlers[1]();
}
