#include "headers/ChecksumEncoder.h"
#include "../Maths/headers/LogicLong.h"

void ChecksumEncoder::destruct() {
    _checksum = 0;
}

bool ChecksumEncoder::IsCheckSumOnlyMode() {
    return true;
}

uint32_t ChecksumEncoder::RotateRight(uint32_t value, int count) {
    return (value >> count) | (value << (32 - count));
}

void ChecksumEncoder::writeStringReference(std::string value) {
    _checksum = (uint32_t)(value.size() + RotateRight(_checksum, 31) + 38);
}


void ChecksumEncoder::writeString(std::string value) {
    _checksum = (uint32_t)((!value.empty() ? value.size() + 28 : 27) + RotateRight(_checksum, 31));
}

bool ChecksumEncoder::writeBoolean(bool value) {
    _checksum = (uint32_t)((value ? 13 : 7) + RotateRight(_checksum, 31));
    return value;
}

void ChecksumEncoder::writeInt(int value) {
    _checksum = (uint32_t)(value + RotateRight(_checksum, 31) + 9);
}

void ChecksumEncoder::writeBytes(uint8_t *bytes, int length) {
    _checksum = (uint32_t)(((bytes != nullptr ? length + 28 : 27) + (_checksum >> 31)) | (_checksum << (32 - 31)));
}

int ChecksumEncoder::writeByte(uint8_t value) {
    _checksum = value + RotateRight(_checksum, 31) + 11;
    return value;
}

void ChecksumEncoder::writeShort(short value) {
    _checksum = (uint32_t)(value + RotateRight(_checksum, 31) + 19);
}

int ChecksumEncoder::writeVInt(int value) {
    _checksum = (uint32_t)(value + RotateRight(_checksum, 31) + 33);
    return value;
}

void ChecksumEncoder::writeLongLong(LogicLong value) {
    _checksum = (uint32_t)(value + RotateRight(_checksum, 31) + 67);
}

bool ChecksumEncoder::IsByteStream() {
    return false;
}

