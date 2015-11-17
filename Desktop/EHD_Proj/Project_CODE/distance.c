#include <avr/io.h>
#include <avr/delay.h>



//#include "lcd.h"

//declaring constants for use in calculation of distance

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
/*    if (adc_value + sensor.b <= 0)
    {
        return -1;
    }
 */
//    return sensor.a / (adc_value + sensor.b) - sensor.k;

    return 6050/adc_value;
}

void displayOnLed(signed short distance){
    if( distance>=10 && distance<20 ){
    PORTB= 0b11111110;
    }
    else if( distance>=20 && distance<30 ){
    PORTB= 0b11111100;
    }
    else if( distance>=30 && distance<40 ){
    PORTB= 0b11111000;
    }
    else if( distance>=40 && distance<50 ){
    PORTB= 0b11110000;
    }
    else if( distance>=50 && distance<60 ){
    PORTB= 0b11100000;
    }
    else if( distance>=60 && distance<70 ){
    PORTB= 0b11000000;
    }
    else if( distance>=70 && distance<80 ){
    PORTB= 0b10000000;
    }
    else{
    PORTB= 0b00000000;

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
      _delay_ms(500);
   }
}
