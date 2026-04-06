#pragma once
#include <string>
#include <vector>
#include <netinet/in.h>

#include "ChecksumEncoder.h"

#include "../headers/ByteStream.h"
#include "../../Maths/headers/LogicLong.h"

class LogicLong;

class ByteStream : public ChecksumEncoder
{
private:
    int _bitIdx;
    uint8_t* _buffer;
    int _bufferSize;
    int _length;
    int _offset;

public:
    ByteStream(int capacity);
    ByteStream(uint8_t* buffer, int length);

    void destruct();
    bool isCheckSumOnlyMode();
    bool isByteStream();

    void writeStringReference(std::string value) override;
    void writeString(std::string value) override;
    bool writeBoolean(bool value) override;
    void writeInt(int value) override;
    void writeBytes(uint8_t* values, int length) override;
    int writeByte(uint8_t value) override;
    void writeShort(short value) override;
    int writeVInt(int value) override;
    void writeLongLong(LogicLong value) override;
    virtual void writeLong(LogicLong value);
    void writeBytesWithoutLength(uint8_t* value, int length);
    void writeIntToByteArray(int value);
    void writeVLong(LogicLong value);

    std::string readStringReference(int maxCapacity = 900000);
    std::string readString(int maxCapacity = 9000000);
    bool readBoolean();
    int readInt();
    int readVInt();
    LogicLong readLongLong();
    LogicLong readLong();
    int readBytesLength();
    uint8_t* readBytes(int length, int maxCapacity);
    uint8_t readByte();
    short readShort();
    int readIntInternal();
    long readVLong();
    void ensureCapacity(int capacity);
    void setByteArray(uint8_t* buffer, int length);
    void resetOffset();
    int getOffset();
    int getLength();
    uint8_t* getByteArray();
};