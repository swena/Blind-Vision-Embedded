#include <stdio.h>
#include <homelab/adc.h>
#include <homelab/delay.h>
#include <homelab/module/sensors.h>
#include <homelab/module/lcd_alpha.h>
typedef const struct
{
	const signed short a;
	const signed short b;
	const signed short k;
}
ir_distance_sensor;
 
//
// The object of the parameters of GP2Y0A21YK sensor
// 
const ir_distance_sensor GP2Y0A21YK = { 5461, -17, 2 };
 
//
// Converting the values of the IR distance sensor to centimeters
// Returns -1, if the conversion did not succeed
//
signed short ir_distance_calculate_cm(ir_distance_sensor sensor,
	unsigned short adc_value)
{
	if (adc_value + sensor.b <= 0)
	{
		return -1;
	}
 
	return sensor.a / (adc_value + sensor.b) - sensor.k;
} 
//
// Main program
//
int main(void)
{	
	unsigned short value;
	signed short distance;	
	char text[16];
 
	// External sensor selection
	pin ex_sensors = PIN(G, 0);
	pin_setup_output(ex_sensors);
	pin_set(ex_sensors);
 
	// Initialization of LCD
	lcd_alpha_init(LCD_ALPHA_DISP_ON);
 
	// Clearing the LCD
	lcd_alpha_clear();
 
	// Name of the program
	lcd_alpha_write_string("Distance sensor");
 
	// Setup of the ADC
	adc_init(ADC_REF_AVCC, ADC_PRESCALE_8);
 
	// Endless loop
	while (true)
	{
		// Reading the 4 times rounded value of output voltage
		value = adc_get_average_value(0, 4);		
 
		// Conversing ADC value to distance
		distance = ir_distance_calculate_cm(GP2Y0A21YK, value);
 
		// Was the calculation successful?
		if (distance >= 0)
		{			
			// Conversing distance to text
			sprintf(text, "%d cm   ", distance);
		}
		else
		{		
			// Creating the text for unknown distance
			sprintf(text, "? cm   ");
		}
 
		// Displaying the text on the LCD
		lcd_alpha_goto_xy(0, 1);
		lcd_alpha_write_string(text);
 
		// Break
		sw_delay_ms(500);
	}
}
