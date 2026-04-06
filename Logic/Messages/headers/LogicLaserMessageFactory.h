#pragma once
#include <sys/types.h>

class PiranhaMessage;

class LogicLaserMessageFactory {
    public:

    PiranhaMessage* createMessageByType(ushort messageId);
};
