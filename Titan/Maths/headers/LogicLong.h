#pragma once

class ByteStream;
class ChecksumEncoder;

class LogicLong {
    private:
    int highInt;
    int lowInt;
    public:
    LogicLong();
    LogicLong(int highInt, int lowInt);
    void set(int high, int low);
    static long ToLong(int high, int low);
    LogicLong Clone();
    bool isZero();
    int GetHigherInt();
    int GetLowerInt();
    LogicLong Decode(ByteStream& stream);
    LogicLong Encode(ChecksumEncoder& checksumEncoder);
    LogicLong Encode(ByteStream& stream);
    int HashCode();
    int GetHashCode();
    operator long() const {
        return ToLong(highInt, lowInt);
    }
};

