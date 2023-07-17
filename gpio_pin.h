#ifndef __GPIO_PIN__
#define __GPIO_PIN__
 
class GPIO_Pin
{
 
public:
   // enum registrindo valores para construção da classe.
   typedef void (* handlerFunc)(void); // ponteiro salvo para objeto de interrupção
   static handlerFunc handlers[2];
   enum GPIO_Port_t
   {
       GPIO_PORTB = 0x23,
       GPIO_PORTC = 0x26,
       GPIO_PORTD = 0x29
   };
   enum GPIO_Directon_t
   {
       GPIO_INPUT = 0,
       GPIO_OUTPUT = 1,
       GPIO_INT_LOW = 2,
       GPIO_INT_CHANGE = 3,
       GPIO_INT_FALLING = 4,
       GPIO_INT_RISING = 5
   };
   enum GPIO_PinNumber_t
   {
       GPIO_PIN_0 = 0,
       GPIO_PIN_1,
       GPIO_PIN_2,
       GPIO_PIN_3,
       GPIO_PIN_4,
       GPIO_PIN_5,
       GPIO_PIN_6,
       GPIO_PIN_7,
   };
 
   GPIO_Pin(GPIO_Port_t _port,
            GPIO_PinNumber_t _pin, GPIO_Directon_t _dir, handlerFunc _func = 0)
   {
       port = (PortRegisters_t *)_port;
       pin_mask = 1 << _pin;
       if (_dir == GPIO_INPUT)
       {
           //*DDRD &= ~botao1_mask
           port->ddr &= ~pin_mask;
       }
       else if (_dir == GPIO_OUTPUT)
       {
           port->ddr |= pin_mask;
       }
       else // interrupção só funciona na int0 e int1 ,pinos 2 e 3
       {
           int interrupt = _pin - 2; //verificando pino e para ver qual interrupção irá ser
           int edge = (int) _dir -2; //direção será a enumeração para ver a configuração no registrador
           /*
           (    x x x x ? ? x x
           & ~  0 0 0 0 1 1 0 0 -> 3 << 2 * interrupt
           ) =   1 1 1 1 0 0 1 1
           (    x x x x 0 0 x x 
           |    0 0 0 0 edge 0 0
           ) =   eicrta
           */
          unsigned char mask = (3<< interrupt*2);
           *eicra = (*eicra & ~ mask ) | (edge << interrupt * 2); //ajustar os bits de uma interrupção de interesse,primeiro zera os bits ao inverter a maske dps deslocar eles para a o valor da interrupção.
           *eimsk |= (1<< interrupt); //ligando interrupção pelo seu tipo
           handlers[interrupt] = _func; //salvando objeto
       }
   }
   bool get()
   {
       // return *PIND & botao1_mask;
       return (port->pin & pin_mask) > 0; // pin para ler
       // return port->pin & pin_mask; //pin para ler
   }
   void set(bool value)
   {
       //*PORTB = *PORTB | led_mask;
 
       if (value == 1)
       {
           port->port |= pin_mask;
       }
       else
       {
           port->port &= ~pin_mask; // port para escrever
       }
   }
   void clear()
   {
       //*PORTB &= ~led_mask;
       port->port &= pin_mask;
   }
 
private:
   struct PortRegisters_t
   {
       volatile unsigned char pin;
       volatile unsigned char ddr;
       volatile unsigned char port;
   };
   static volatile unsigned char *eicra ; //ponteiros compartilhados para cada GPIO e não um para cada GPIO
   static volatile unsigned char *eimsk ;
   PortRegisters_t *port;
   unsigned char pin_mask; // calcular sempre a mascara e armazenar.
   // mapemeanto da struct para endereçamento de memória.
  
};
#endif
