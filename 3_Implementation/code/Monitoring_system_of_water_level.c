#include <avr/io.h>
#include <util/delay.h>


void USARTInit(uint16_t ubrr_value)
{
    
    //Data is received
    UBRR0L = ubrr_value;
    
    UBRR0H = (ubrr_value>>8)&0X00ff ;
    
    UCSR0C = (1<<UMSEL00)|(1<<UCSZ01)|(1<<UCSZ00);

    //Transmitter and  Receiver are working
    UCSR0B = (1<<RXEN0)|(1<<TXEN0)|(1<<RXCIE0)|(1<<TXCIE0);
}

char USARTReadChar()
{
    //Pls wait
    while(!(UCSR0A & (1<<RXC0)))
    {
        
        //...
        
    }
    return UDR0;
}

void USARTWriteChar(char data)
{
    // Transmitter is getting ready
    while (!(UCSR0A & (1<<UDRE0)))
    {
        
        //...
        
    }
    
    //TO WRITE THE DATA TO USART BUFFER
    UDR0 = data;
}
