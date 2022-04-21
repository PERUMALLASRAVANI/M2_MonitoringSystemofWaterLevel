#include <avr/io.h>
#include <util/delay.h>

void USARTInit(uint16_t ubrr_value)
{
    //Set Baud rate
    UBRR0L = ubrr_value;
    UBRR0H = (ubrr_value>>8)&0X00ff ;
    UCSR0C = (1<<UMSEL00)|(1<<UCSZ01)|(1<<UCSZ00);

    //Enable Transmitter Receiver
    UCSR0B = (1<<RXEN0)|(1<<TXEN0)|(1<<RXCIE0)|(1<<TXCIE0);
}

char USARTReadChar()
{
    //Wait until data is available
    while(!(UCSR0A & (1<<RXC0)))
    {
        //DO NOTHING
    }
    return UDR0;
}

void USARTWriteChar(char data)
{
    //wait until transmitter is ready
    while (!(UCSR0A & (1<<UDRE0)))
    {
        //DO  NOTHING
    }
    //TO WRITE THE DATA TO USART BUFFER
    UDR0 = data;
}
