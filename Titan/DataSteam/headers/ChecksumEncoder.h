#pragma once
#include <string>
#include <sys/types.h>

class LogicLong;

class ChecksumEncoder {
    private:
    uint _checksum;
    public:

    void destruct();
    virtual bool IsCheckSumOnlyMode();
    static uint RotateRight(uint value, int count);
    virtual void writeStringReference(std::string value);
    virtual void writeString(std::string value);
    virtual bool writeBoolean(bool value);
    virtual void writeInt(int value);
    virtual void writeBytes(uint8_t* bytes, int length);
    virtual int writeByte(uint8_t value);
    virtual void writeShort(short value);
    virtual int writeVInt(int value);
    virtual void writeLongLong(LogicLong value);//logiclong
    virtual bool IsByteStream();
};

