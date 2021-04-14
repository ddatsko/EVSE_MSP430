#include "i2c.h"
#include "messages.h"


char *readBuf = (char *)0;
char *writeBuf = (char *)0;

char *nextReadBuf = (char *)0;
char *nextWriteBuf = (char *)0;

char dummy;
unsigned char curMessageIndex;
char reading;


#pragma vector=USCIAB0TX_VECTOR
__interrupt void UsciI2CDataIsr(void)
{
    if (curMessageIndex == MAX_MSG_LENGTH) {
        // Maybe, should send a message about the situation
        curMessageIndex = 0;
    }
    if (IFG2 & UCB0TXIFG) {     // transmit request
        reading = 0;
        if (writeBuf == (char *)0) {
            UCB0TXBUF = 0;  // Sending 0-s if the response is not ready yet
        } else {
            UCB0TXBUF = writeBuf[curMessageIndex++];
        }
    } else {        // receiving a byte
        reading = 1;
        if (readBuf != (char *)0) {
            readBuf[curMessageIndex++] = UCB0RXBUF;
        } else {
            dummy = UCB0RXBUF;
        }
    }
}


#pragma vector=USCIAB0RX_VECTOR
__interrupt void UsciI2CStateIsr(void)
{
    if (UCB0STAT & UCSTTIFG) {      // Start condition interrupt
        UCB0STAT &= ~UCSTTIFG;      // Clear start condition int flag
        curMessageIndex = 0;     // reset the position of message pointe
        writeBuf = nextWriteBuf;
        readBuf = nextReadBuf;
    } else if (UCB0STAT & UCSTPIFG) {       // Stop condition interrupt
        UCB0STAT &= ~UCSTPIFG;      // Clear stop condition int flag

        if (reading) {
            nextReadBuf = 0;
            sendMessage(READ_STOP);
        } else {
            nextWriteBuf = 0;
            sendMessage(WRITE_STOP);
        }
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

