#ifndef INCLUDE_I2C_H_
#define INCLUDE_I2C_H_

#include <msp430.h>


#define SDA_PIN BIT7
#define SCL_PIN BIT6
#define OWN_ADDRESS 1

void I2CInit();

char* I2CGetReceivedMessage();

char I2CReadByte();

void I2CWriteByte(char byte);

#endif /* INCLUDE_I2C_H_ */
