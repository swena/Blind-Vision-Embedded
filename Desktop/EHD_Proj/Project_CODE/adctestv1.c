#include <avr/io.h>
#include <avr/delay.h>




//SOUND Begin--------------------------------------------------------------

#define F_CPU 16000000UL
#define SPEAKER_PORT    PORTC
#define SPEAKER_DDR      DDRC
#define SPEAKER_PIN      7

// Prototypes used
void PLAYNOTE(float duration, float frequency);



// Function to play a note given the duration and frequency
void PLAYNOTE(float duration, float frequency)
{
    // Physics variables
    long int i,cycles;
    float half_period;   
    float wavelength;
   
    wavelength=(1/frequency)*1000;     
// standard physics formula         
    cycles=duration/wavelength;       
// the number of cycles
    half_period = wavelength/2;       
// the time between the toggle

    // Data direction register Pin 7 is set for output
    SPEAKER_DDR |= (1 << SPEAKER_PIN);

    for (i=0;i<cycles;i++)            
// The output pin 7 is toggled for the
                                      
// 'cycles' number of times.
    {
        _delay_ms(half_period);                
// Wait 1 half wavelength
        SPEAKER_PORT |= (1 << SPEAKER_PIN);    
// Output 5v to port Pin 7
        _delay_ms(half_period);                
// Wait 1 half wavelength
        SPEAKER_PORT &= ~(1 << SPEAKER_PIN);   
// 0v at port pin 7
    }

    return;                                     
// return to main()
}

//Sound end -----------------------------------------------------------


typedef const struct
{
	const signed short  a;
	const signed short b;
	const signed short k;
}
ir_distance_sensor;
 
//
// The object of the parameters of GP2Y0A21YK sensor
// 
const ir_distance_sensor GP2Y0A21YK = { 5461, -17, 2 };


//end of declaration

void InitADC()
{
ADMUX=(1<<REFS0);                         // For Aref=AVcc;
ADCSRA=(1<<ADEN)|(1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0); //Rrescalar div factor =128
}

uint16_t ReadADC(uint8_t ch)
{
   //Select ADC Channel ch must be 0-7
   ch=ch&0b00000111;
   ADMUX|=ch;

   //Start Single conversion
   ADCSRA|=(1<<ADSC);

   //Wait for conversion to complete
   while(!(ADCSRA & (1<<ADIF)));

   //Clear ADIF by writing one to it
   //Note you may be wondering why we have write one to clear it
   //This is standard way of clearing bits in io as said in datasheets.
   //The code writes '1' but it result in setting bit to '0' !!!

   ADCSRA|=(1<<ADIF);

   return(ADC);
}





//Calculating distance from voltage
signed short ir_distance_calculate_cm(ir_distance_sensor sensor,uint16_t adc_value)
{
/*	if (adc_value + sensor.b <= 0)
	{
		return -1;
	}
 */
//	return sensor.a / (adc_value + sensor.b) - sensor.k;

	return 6050/adc_value;
} 

void displayOnLed(signed short distance){
	if( distance>=10 && distance<20 ){
		PORTB = 10101010;
	    PLAYNOTE(10,1900);
	}
	else if( distance>=20 && distance<30 ){
		PORTB = 01010101;
	    PLAYNOTE(10,1600);
	}
	else if( distance>=30 && distance<40 ){
		PORTB = 10101010;
	    PLAYNOTE(10,1300);
	}
	else if( distance>=40 && distance<50 ){
	    PLAYNOTE(10,1000);
		PORTB = 01010101;
	}
	else if( distance>=50 && distance<60 ){
	    PLAYNOTE(10,700);
		PORTB = 10101010;
	}
	else if( distance>=60 && distance<70 ){
	    PLAYNOTE(10,400);
		PORTB = 01010101;
	}
	else if( distance>=70 && distance<80 ){
	    PLAYNOTE(10,100);
		PORTB = 10101010;
	}

	else{
	

	}

}

void main()
{
   uint16_t adc_result;
//int adc_result;
   signed short distance;
   DDRB = 0xFF;

/*
   //Initialize LCD
   LCDInit(LS_BLINK|LS_ULINE);
   LCDClear();
*/
   //Initialize ADC
   InitADC();

/*
   //Put some intro text into LCD
   LCDWriteString("ADC Test");
   LCDWriteStringXY(0,1,"ADC=");
*/
   while(1)
   {
      adc_result=ReadADC(0);           // Read Analog value from channel-0
//    LCDWriteIntXY(4,1,adc_result,4); //Print the value in 4th column second line
      distance = ir_distance_calculate_cm(GP2Y0A21YK,adc_result);
      displayOnLed(distance);
      _delay_ms(10);
   }
}



