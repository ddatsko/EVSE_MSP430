
#ifndef AVSE_TOOLS
#define AVSE_TOOLS

#include <msp430.h>


#define AVSE_PORT_INPUT P2IN
#define AVSE_PORT_OUTPUT P2OUT
#define AVSE_PORT_DIR P2DIR
#define AVSE_PORT_REN P2REN
#define AVSE_INT_IE P2IE
#define AVSE_INT_IES P2IES
#define AVSE_INT_IFG P2IFG
#define AVSE_BIT BIT0
#define AVSE_VECTOR PORT2_VECTOR

#define ADC_INPUT_PIN BIT4         // Port is always 1
#define ADC_INPUT_CHANNEL INCH_4   // Should be the same as the ADC_INPUT_PIN

#define PWM_PIN BIT2   //Port is now always 1. Cannot use any pin (see documetation)


void gfIntInit();
void gfIntReset();
void adcInit();
int measureAdcData();
void pwmInit();


#endif
