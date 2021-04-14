#include <I2CSwitch.h>
#include <msp430.h>
#include "messages.h"
#include "i2c.h"


#define STATE_INIT 0
#define STATE_MESSAGE_PROCESS 1

// Buffers for reading the mssage to and for sending the message from
char writeBufs[2][MAX_MSG_LENGTH];
unsigned char curWriteBuf;

char readBufs[2][MAX_MSG_LENGTH];
unsigned char curReadBuf;

char curState;


void I2CSwitchInit() {
    curWriteBuf = 0;
    curReadBuf = 0;
    nextReadBuf = readBufs[curReadBuf];
    curState = STATE_INIT;
}


unsigned char packetNumber = 0; // just for test
void processMessage(char *msg, char *responseDest) {
    packetNumber++;
    unsigned int i;
    for (i = 0; i < MAX_MSG_LENGTH; i++) {
        responseDest[i] = packetNumber;
    }
}


void I2CSwitchProcess() {

    if (curState == STATE_INIT) {
            if (getMessage(READ_STOP)) {
                curReadBuf ^= 1;
                nextReadBuf = readBufs[curReadBuf];
                curState = STATE_MESSAGE_PROCESS;
            }
    }
    if (curState == STATE_MESSAGE_PROCESS) {
            processMessage(readBufs[curReadBuf ^ 1u], writeBufs[curWriteBuf ^ 1u]);
            if (!getMessage(READ_STOP)) {
                curWriteBuf ^= 1;
                nextWriteBuf = writeBufs[curWriteBuf];
                curState = STATE_INIT;
            } else {    // If a new message was got during the processing, do not respond to the previous one
                curReadBuf ^= 1;
                nextReadBuf = readBufs[curReadBuf];
            }
    }

}
