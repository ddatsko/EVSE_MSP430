#include "i2c.h"
#include "messages.h"

char message[256];
unsigned char curMessageChar;

inline void transmitCallback() {
    UCB0TXBUF = 10;
}

#pragma vector=USCIAB0TX_VECTOR
__interrupt void UsciI2CDataIsr(void)
{
    if (IFG2 & UCB0TXIFG) {     // transmit request
        transmitCallback();

    } else {        // receiving a byte
        message[curMessageChar++] = UCB0RXBUF;
    }
}


#pragma vector=USCIAB0RX_VECTOR
__interrupt void UsciI2CStateIsr(void)
{
    if (UCB0STAT & UCSTTIFG) {      // Start condition interrupt
        UCB0STAT &= ~UCSTTIFG;      // Clear start condition int flag
        curMessageChar = 0;     // reset the position of message pointer
    } else if (UCB0STAT & UCSTPIFG) {       // Stop condition interrupt
        UCB0STAT &= ~UCSTPIFG;      // Clear stop condition int flag
    }
}


void I2CInit() {
    P1SEL |= SDA_PIN + SCL_PIN;
    P1SEL2 |= SDA_PIN + SCL_PIN;        // Assign SDA and SCL pins to USCI_B0
    UCB0CTL1 |= UCSWRST;        // Enable software reset to safely modify the parameters
    UCB0CTL0 = UCMODE_3 + UCSYNC;       // 7-bit addressing, I2C slave mode

    UCB0I2COA = OWN_ADDRESS;        // Set own I2C address
    UCB0CTL1 &= ~UCSWRST;       // Disable software reset mode to make I2C run

    IE2 |= UCB0TXIE + UCB0RXIE;     // Enable RX and TX interrupts
    UCB0I2CIE |= UCSTTIE + UCSTPIE;     // Enable STT interrupt

}


char I2CReadByte() {
    return UCB0RXBUF;
}

void I2CWriteByte(char byte) {
    UCB0TXBUF = byte;
}
