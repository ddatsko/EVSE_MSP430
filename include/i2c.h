#ifndef INCLUDE_I2C_H_
#define INCLUDE_I2C_H_

#include <msp430.h>


#define SDA_PIN BIT7
#define SCL_PIN BIT6
#define OWN_ADDRESS 1
#define MAX_MSG_LENGTH 100


extern char *nextReadBuf;
extern char *nextWriteBuf;



void I2CInit();

char* I2CGetReceivedMessage();


#endif /* INCLUDE_I2C_H_ */
