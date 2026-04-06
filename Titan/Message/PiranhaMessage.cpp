#include "headers/PiranhaMessage.h"

#include "headers/PiranhaMessage.h"

PiranhaMessage::PiranhaMessage(int capacity)
    : _stream(capacity)
{
}

void PiranhaMessage::encode() {

}

void PiranhaMessage::decode() {

}

int PiranhaMessage::getMessageType() {
    return 0;
}

ByteStream &PiranhaMessage::getByteStream() {
    return _stream;
}

int PiranhaMessage::getServiceNodeType() {
    return 0;
}

int PiranhaMessage::getEncodingLength() {
    return this->_stream.getOffset();
}

void PiranhaMessage::setMessageBytes(uint8_t* bytes, int length) {
    this->_stream.setByteArray(bytes, length);
}

uint8_t* PiranhaMessage::getMessageBytes() {
    return this->_stream.getByteArray();
}