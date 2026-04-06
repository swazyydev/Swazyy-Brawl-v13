#include "headers/LogicLong.h"
#include "../DataSteam/headers/ByteStream.h"
#include "../DataSteam/headers/ChecksumEncoder.h"

#include <cstdint>
#include <sys/types.h>

LogicLong::LogicLong() {

}
LogicLong::LogicLong(int high, int low) {
    highInt = high;
    lowInt = low;
}

void LogicLong::set(int high, int low) {
    highInt = high;
    lowInt = low;
}

long LogicLong::ToLong(int high, int low) {
    return ((long)high << 32) | (uint32_t)low;
}

LogicLong LogicLong::Clone() {
    return LogicLong(highInt, lowInt);
}

bool LogicLong::isZero() {
    return highInt == 0 && lowInt == 0;
}

int LogicLong::GetHigherInt() {
    return highInt;
}

int LogicLong::GetLowerInt() {
    return lowInt;
}

LogicLong LogicLong::Decode(ByteStream& stream) {
    highInt = stream.readInt();
    lowInt = stream.readInt();

    return *this;
}

LogicLong LogicLong::Encode(ChecksumEncoder& stream) {
    stream.writeInt(highInt);
    stream.writeInt(lowInt);
    return *this;
}


LogicLong LogicLong::Encode(ByteStream& stream) {
    stream.writeInt(highInt);
    stream.writeInt(lowInt);
    return *this;
}

int LogicLong::HashCode()
{
    return lowInt + 31 * highInt;
}

int LogicLong::GetHashCode()
{
    return HashCode();
}

