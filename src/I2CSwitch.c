#include <msp430.h>
#include "i2c_switch.h"
#include "messages.h"
#include "i2c.h"


#define STATE_INIT 0
#define STATE_MSG_IS_READING 1
#define STATE_MSG_IS_READ 2
#define STATE_CALC_RESPONSE 3
#define STATE_SEND_RESP_NOT_READY 4
#define STATE_SEND_RESP 5

char calculating;
char newByte;
char respReady;
char curState;

char receiveMsgIndex;
char sendMsgIndex;
char sendMsgSize;
char buf1[50];
char buf2[50];


char *receivingBuf;
char *calculatingBuf;

char respBuf[50];

void I2CSwitchInit() {

    calculating = 0;
    newByte = 0;
    respReady = 0;
    curState = STATE_INIT;
}


void I2CProcess() {


    switch(curState) {
        case STATE_INIT:
            if (getMessage(WRITE_BYTE_REQUEST) == 1) {
                if (respReady == 1) {
                    respReady = 0;
                    curState = STATE_SEND_RESP;
                }
            } else if (getMessage(START_SIGNAL) == 1) {
                receiveMsgIndex = 0;
                curState = STATE_MSG_IS_READING;
            } else if (getMessage(STOP_SIGNAL) == 1 || getMessage(READ_BYTE_READY) == 1) {
                // Maybe go to some error state here
            }

            break;



        case STATE_MSG_IS_READING:
            if (getMessage(READ_BYTE_READY) == 1) {
                receivingBuf[receiveMsgIndex++] = I2CReadByte();
            }
            else if (getMessage(STOP_SIGNAL) == 1) {
                if (calculating) {

                } else {
                     char *tmp = receivingBuf;
                     receivingBuf = calculatingBuf;
                     calculatingBuf = tmp;
                }
            }

            break;

        case STATE_MSG_IS_READ:


            break;
        case STATE_CALC_RESPONSE:

            break;

        case STATE_SEND_RESP_NOT_READY:

            break;

        case STATE_SEND_RESP:


            break;
    }
}
