#define ULTRASONIC_TRIG_PIN 12
#define ULTRASONIC_ECHO_PIN 13
HCSR04 ultrasonic(ULTRASONIC_TRIG_PIN,ULTRASONIC_ECHO_PIN);
NXTBluetooth bluetooth(2, 3, 1, 10);

void USARTInit(uint16_t );
char USARTReadChar();
void USARTWriteChar(char *);
unsigned char mydata;
int i,duration=0,distance=0;

//String message;
//Bluetooth message

void USARTInit(uint16_t ubrr_value)
{
    
    //Data is received
    UBRR0L = ubrr_value;
    
    UBRR0H = (ubrr_value>>8)&0X00ff ;
    
    UCSR0C = (1<<UMSEL00)|(1<<UCSZ01)|(1<<UCSZ00);

    //Transmitter and Receiver are working
    UCSR0B = (1<<RXEN0)|(1<<TXEN0)|(1<<RXCIE0)|(1<<TXCIE0);
    
}

char USARTReadChar()
{
    //Please wait 
    while(!(UCSR0A & (1<<RXC0)))
    {
        //...
    }
    
    return UDR0;
}

void USARTWriteChar(char *data)
{
    //Transmitter is getting ready
    
    while (!(UCSR0A & (1<<UDRE0)))
    {
        //...
    }
    // WRITE THE DATA TO USART BUFFER
    UDR0 = *data;
    
}


int main(void)
{
    USARTInit(103);
    
    DDRB |= (1<<DDB2)|(1<<DDB3)|(1<<DDB0)|(1<<DDB4); /*B2&B3 are indicator LED's,B0 is Ultrasonic Sensor Trigger O/P,B4 Motor load*/
    DDRB &= ~(1<<DDB1);                              /*B1 is Ultrasonic Sensor Echo I/P*/
    while(1)
    {
        USARTInit(103);
        
        //duration = pulseIn(PORTB1,HIGH);
        //distance = (duration/2)*2.91;
        mydata = USARTReadChar();
        
        if (mydata=='A')
        {
            PORTB |=(1<<PORTB2);
            PORTB |=(1<<PORTB4);
            PORTB &=~(1<<PORTB3);
            /*for (i = 0; i < 10; i += 1)
            {                                   
            //FOR BLUETOOTH MESSAGE TRANSFER
                message = String("Motor Turned On " + String(i + 1) + "!");
            }
            */USARTWriteChar("Water level's low, Motor Turned On");
            /*If interfaced, Message will be sent to Connected Bluetooth user*/
            //bluetooth.write(message, i);
            //Loads
        }
        else if(mydata=='B'){
            PORTB &=~(1<<PORTB2);
            PORTB &=~(1<<PORTB4);
            PORTB |=(1<<PORTB3);
            
            /*for (i = 0; i < 10; i += 1)
            {                                    //FOR BLUETOOTH MESSAGE TRANSFER
              
              message = String("Motor Turned Off " + String(i + 1) + "!");
            }
            */
            USARTWriteChar("Water level's High, Motor Turned Off");
            
            /*If interfaced, Message will be sent to Connected Bluetooth user*/
            //bluetooth.write(message, i);  
            /*note that messages can't exede 59 characters including the null terminator*/
        }
        //bluetooth.update();
    }
    return 0;
}
