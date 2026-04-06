#pragma once
#include <cstdint>

#include "../../DataSteam/headers/ByteStream.h"

class PiranhaMessage {
    public:

    PiranhaMessage(int capacity);

    ByteStream _stream;
    int version;

    virtual void encode();
    virtual void decode();

    virtual int getMessageType();
    virtual int getServiceNodeType();

    ByteStream& getByteStream();

    int getEncodingLength();
    void setMessageBytes(uint8_t* bytes, int length);

    uint8_t* getMessageBytes();
};
