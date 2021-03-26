#include <msp430.h>				
#include "avse_tools.h"




void main(void)
{
    WDTCTL = WDTPW + WDTHOLD; // Stop watchdog timer
    P1DIR |= 0x01;
    P1DIR &= ~(BIT4);
    adc_init();
    gf_int_init();
    volatile int adc_data;
    volatile int adc_voltage;
    pwm_init(500);
    _BIS_SR(LPM0_bits + GIE);  // Low power mode 0


	while(1)
	{
	    adc_data = measure_adc_data();
	    adc_voltage = (adc_data * 3);
	    _nop();
	}
}
