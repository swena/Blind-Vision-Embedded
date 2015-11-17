#include<avr/io.h>
#include<avr/delay.h>

int main()
{
	DDRB = 0xFF;
	
	while(1)
	{
		PORTB = 0x11;
		_delay_ms(50);
		PORTB = 0x22;
		_delay_ms(50);
		PORTB = 0x44;
		_delay_ms(50);
		PORTB = 0x88;
		_delay_ms(50);
		PORTB = 0x11;
		_delay_ms(50);
		PORTB = 0x22;
		_delay_ms(50);
		PORTB = 0x44;
		_delay_ms(50);
		PORTB = 0x88;
		_delay_ms(50);
	}
}
