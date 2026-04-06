#include "headers/OwnHomeDataMessage.h"

#include <iostream>
#include <ostream>

OwnHomeDataMessage::OwnHomeDataMessage()
    : PiranhaMessage(10)
{
}

void OwnHomeDataMessage::encode() {
    clientHome.encode(_stream);
    clientAvatar.encode(_stream);

    _stream.writeVInt(0);
}

int OwnHomeDataMessage::getMessageType() {
    return 24101;
}

int OwnHomeDataMessage::getServiceNodeType() {
    return 9;
}