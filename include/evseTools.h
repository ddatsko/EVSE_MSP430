
#ifndef EVSE_TOOLS
#define EVSE_TOOLS

#include <msp430.h>


#define EVSE_PORT_INPUT P2IN
#define EVSE_PORT_OUTPUT P2OUT
#define EVSE_PORT_DIR P2DIR
#define EVSE_PORT_REN P2REN
#define EVSE_INT_IE P2IE
#define EVSE_INT_IES P2IES
#define EVSE_INT_IFG P2IFG
#define EVSE_BIT BIT0
#define EVSE_VECTOR PORT2_VECTOR

#define ADC_INPUT_PIN BIT4         // Port is always 1
#define ADC_INPUT_CHANNEL INCH_4   // Should be the same as the ADC_INPUT_PIN

#define PWM_PIN BIT2   //Port is now always 1. Cannot use any pin (see documetation)


void gfIntInit();
void gfIntReset();
void adcInit();
int emasureAdcData();
void pwmInit();


#endif
