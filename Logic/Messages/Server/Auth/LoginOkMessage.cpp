#include "headers/LoginOkMessage.h"

#include <iostream>
#include <ostream>

LoginOkMessage::LoginOkMessage()
    : PiranhaMessage(10)
{
}

void LoginOkMessage::encode() {
    _stream.writeLong(LogicLong(1, 0));
    _stream.writeLong(LogicLong(1, 0));

    _stream.writeString("t.me/spookyswazyy");
    _stream.writeString("");
    _stream.writeString("");
}

int LoginOkMessage::getMessageType() {
    return 20104;
}

int LoginOkMessage::getServiceNodeType() {
    return 1;
}