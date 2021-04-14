
#ifndef INCLUDE_MESSAGES_H_
#define INCLUDE_MESSAGES_H_


#define NUMBER_OF_MESSAGES 2
#define READ_STOP 0
#define WRITE_STOP 0

void messagesInit();

void sendMessage(unsigned char message);

char getMessage(unsigned char message);

#endif
