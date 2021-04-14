#include <evseTools.h>
#include <msp430.h>
#include "i2c.h"



void main(void)
{
    WDTCTL = WDTPW + WDTHOLD; // Stop watchdog timer
    DCOCTL = DCO0 + DCO1 + DCO2;

    I2CInit();

    BCSCTL1 = CALBC1_16MHZ;
    DCOCTL  = CALDCO_16MHZ;


    P1DIR |= 0x01;
    P1DIR &= ~(BIT4);
    adcInit();
    gfIntInit();
    volatile int adc_data;
    volatile int adc_voltage;
    pwmInit(100);
    _BIS_SR(LPM0_bits + GIE);  // Low power mode 0


	while(1)
	{
	    I2CSwitchProcess();
	}
}

