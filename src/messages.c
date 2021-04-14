#include "messages.h"

char messages[NUMBER_OF_MESSAGES];



void messagesInit() {
    unsigned int i;
    for (i = NUMBER_OF_MESSAGES - 1; i != 0; i--) {
        messages[i] = 0;
    }
}

void sendMessage(unsigned char message) {
    messages[message] = 1;
}

char getMessage(unsigned char message) {
    char res = messages[message];
    messages[message] = 0;
    return res;
}

