#include "headers/LoginMessage.h"

#include <iostream>
#include <ostream>

LoginMessage::LoginMessage()
    : PiranhaMessage(10)
{
}

void LoginMessage::decode() {
    _stream.readInt();
    _stream.readInt();
    _stream.readInt();
    _stream.readInt();
    _stream.readInt();
}

int LoginMessage::getMessageType() {
    return 10101;
}

int LoginMessage::getServiceNodeType() {
    return 1;
}