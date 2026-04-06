#include "./headers/LogicLaserMessageFactory.h"

#include <iostream>
#include <sys/types.h>

#include "Client/Auth/headers/LoginMessage.h"

PiranhaMessage* LogicLaserMessageFactory::createMessageByType(ushort messageId) {
    switch (messageId) {
        case 10101:
            return new LoginMessage();

        default:
            return nullptr;
    }
}