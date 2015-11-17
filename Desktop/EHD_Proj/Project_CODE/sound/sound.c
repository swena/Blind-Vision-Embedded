/**********************************************************
Author:Peter J. Vis
First Written:8 Dec 1999
Last Updated: 12 Dec 2006
Title: R2D2

Microcontroller:ATmega32
Crystal:16Mhz
Platform:Development System

URL:http://www.petervis.com/C/development/introduction.html

LIMITATIONS:
No portion of this work can be used in commercial
applications without written permission.This program can be published in
magazines and articles with previous consent and as long as credit is given
to the author.

POSTCARD:
Send me a postcard / email if you found my code useful. 

PURPOSE:
This program is to test the pizo speaker by generating sound for it. An 8ohms voice coil speaker could also be used with a 2ohms resistor in series.

CIRCUIT:
Pizo Speaker connected to PortC pin PC7


THEORY:

Note    Frequency
-----------------
A         880   
A#        932   
B         988       
C         1047   
C#        1109   
D         1175   
D#        1244   
E         1319   
F         1397   
F#        1480   
G         1568   
G#        1660   

Sound is produced by switching the speaker on and off using a square wave.
The ATmega32 can output a square wave from any of it's pins. The rate at
which the speaker is switched on and off is the frequency.

A standard wave has a wavelength w and frequency f

w = 1/f

       speaker         on            off           on
                 ______________               ________
                |              |             |
        ________|              |_____________|

                |  half period |             |
                |                            |
                |<--    (w) wavelength    -->|     


**********************************************************/


#define F_CPU 16000000UL

#include <avr/io.h>
#include <util/delay.h>


#define SPEAKER_PORT    PORTC
#define SPEAKER_DDR      DDRC
#define SPEAKER_PIN      7

// Prototypes used
void PLAYNOTE(float duration, float frequency);

int main(void)
{

    PLAYNOTE(100,800);
    PLAYNOTE(100,1800);
    PLAYNOTE(100,800);
    PLAYNOTE(100,1800);
    PLAYNOTE(100,100);
    PLAYNOTE(100,2000);
    PLAYNOTE(100,100);
    PLAYNOTE(100,2000);
    PLAYNOTE(100,100);
    PLAYNOTE(100,2000);
    PLAYNOTE(100,100);
    PLAYNOTE(100,2000);

}


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
