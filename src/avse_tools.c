#include "avse_tools.h"



void gfIntInit() {
    AVSE_PORT_REN &= ~(AVSE_BIT);  // Disabe pull-up and pull-down
    AVSE_PORT_DIR &= ~(AVSE_BIT);  // Set pin direction to input

    AVSE_INT_IE |= AVSE_BIT;        // Enable interrupts on pin
    AVSE_INT_IES &= ~(AVSE_BIT);    // Set interrupt on rising edge
    AVSE_INT_IFG &= ~(AVSE_BIT);    // IFG cleared

   // _BIS_SR(LPM4_bits + GIE);        // LPM4 mode
}


#pragma vector=AVSE_VECTOR
__interrupt void inter(void) {
    P1OUT ^= 0x01;   // Toggle LED
    volatile unsigned int i;
    for ( i = 0; i < 10000; i++) {}
    AVSE_INT_IFG &= ~(AVSE_BIT);
}


void gfIntReset() {
    AVSE_PORT_DIR |= AVSE_BIT;       // Set pin direction to output
    AVSE_PORT_OUTPUT &= ~(AVSE_BIT); // Write 0 to the pin
    _nop();
    _nop();
    AVSE_PORT_DIR &= ~(AVSE_BIT);   // Set pin direction to input
}

void adcInit() {

    ADC10CTL0 &= ~(ENC);  // To safely modify other parts of the register



    ADC10AE0 |= ADC_INPUT_PIN;  // Enable Analog input on selected pin



    ADC10CTL0 = SREF_0;         // VR+ = VCC and VR- = VSS
    ADC10CTL0 += ADC10SHT_2;    // 16 � ADC10CLKs
    ADC10CTL0 += ADC10SR;       // Reference buffer supports up to ~50 ksps  (200 ksps if not set)
    ADC10CTL0 += ADC10ON;       // Switch the ADC ON

    ADC10CTL1 = ADC_INPUT_CHANNEL;  // Select single pin as an input channel
    ADC10CTL1 += SHS_0;             // Sample-and-hold source is ADC10SC bit
    ADC10CTL1 += ADC10DIV_1;
    ADC10CTL1 += ADC10SSEL_0;       // Clock source is ADC10OSC (about 5Mhz)
    ADC10CTL1 += CONSEQ_0;          // Single-channel Single-Conversion mode

    ADC10CTL0 |= ENC;               // Enable conversion
}




int measureAdcData() {
    ADC10CTL0 |= ADC10SC;  // Start conversion
    while(ADC10CTL1 & ADC10IFG == 0) {}
    return ADC10MEM;
}


// Any additional Dividers and clock sources should be configured here.
// Currently,the PWM frequency is about 1.05 kHz on MSP430G2553. By decrementing the TA0CCR0 it can be fit to 1 kHz
void pwmInit(int duty_cycle) {  // Duty cycle should be from 0 to 1000
    P1DIR |= PWM_PIN;                  // P1.2 set as output
    P1SEL |= PWM_PIN;                  // P1.2 selected Timer0_A Out1

    /*** Timer0_A Set-Up ***/
    TA0CCR0 |= 1064 - 1;             // PWM Period
    TA0CCTL1 |= OUTMOD_7;           // TA0CCR1 output mode = reset/set
    TA0CCR1 |= duty_cycle;                 // TA0CCR1 PWM duty cycle
    TA0CTL |= TASSEL_2 + MC_1;      // SMCLK, Up Mode (Counts to TA0CCR0)
}
