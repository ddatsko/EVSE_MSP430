
#ifndef INCLUDE_MESSAGES_H_
#define INCLUDE_MESSAGES_H_

#define READ_BYTE_READY 0
#define WRITE_BYTE_REQUEST 1
#define START_SIGNAL 2
#define STOP_SIGNAL 3


void messagesInit();

void sendMessage(unsigned char message);

char getMessage(unsigned char message);

void resetMessage(unsigned char message);

#endif
