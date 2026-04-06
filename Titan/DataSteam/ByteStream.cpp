#include "headers/ByteStream.h"
#include <cstring>
#include <stdexcept>

ByteStream::ByteStream(int capacity)
{
    _buffer = new uint8_t[capacity];
    _bufferSize = capacity;
    _length = 0;
    _offset = 0;
    _bitIdx = 0;
}

ByteStream::ByteStream(uint8_t* buffer, int length)
{
    _length = length;
    _bufferSize = length;
    _buffer = new uint8_t[_length];
    _offset = 0;
    _bitIdx = 0;
    std::memcpy(_buffer, buffer, _length);
}

void ByteStream::destruct()
{
    ChecksumEncoder::destruct();
    delete[] _buffer;
    _buffer = nullptr;
    _bitIdx = 0;
    _length = 0;
    _offset = 0;
}

bool ByteStream::isCheckSumOnlyMode()
{
    return false;
}

void ByteStream::writeStringReference(std::string value)
{
    ChecksumEncoder::writeStringReference(value);
    if (!value.empty())
    {
        ensureCapacity(value.size() + 4);
        writeIntToByteArray(value.size());
        std::memcpy(_buffer + _offset, value.c_str(), value.size());
        _offset += value.size();
    }
    else
    {
        writeIntToByteArray(0);
    }
}

void ByteStream::writeString(std::string value)
{
    ChecksumEncoder::writeString(value);
    if (value.empty())
    {
        writeIntToByteArray(-1);
    }
    else
    {
        ensureCapacity(value.size() + 4);
        writeIntToByteArray(value.size());
        std::memcpy(_buffer + _offset, value.c_str(), value.size());
        _offset += value.size();
    }
}

bool ByteStream::writeBoolean(bool value)
{
    ChecksumEncoder::writeBoolean(value);
    if (_bitIdx == 0)
    {
        ensureCapacity(1);
        _buffer[_offset] = 0;
        _offset++;
    }
    if (value)
    {
        _buffer[_offset - 1] |= (uint8_t)(1 << _bitIdx);
    }
    _bitIdx = (_bitIdx + 1) & 7;
    return value;
}

void ByteStream::writeInt(int value)
{
    ChecksumEncoder::writeInt(value);
    writeIntToByteArray(value);
}

void ByteStream::writeBytes(uint8_t* values, int length)
{
    ChecksumEncoder::writeBytes(values, length);
    if (values != nullptr)
    {
        ensureCapacity(length + 4);
        writeIntToByteArray(length);
        std::memcpy(_buffer + _offset, values, length);
        _offset += length;
    }
    else
    {
        writeIntToByteArray(-1);
    }
}

int ByteStream::writeByte(uint8_t value)
{
    ChecksumEncoder::writeByte(value);
    ensureCapacity(1);
    _bitIdx = 0;
    _buffer[_offset++] = value;
    return value;
}

void ByteStream::writeShort(short value)
{
    ChecksumEncoder::writeShort(value);
    ensureCapacity(2);
    _bitIdx = 0;
    _buffer[_offset++] = (uint8_t)(value >> 8);
    _buffer[_offset++] = (uint8_t)value;
}

int ByteStream::writeVInt(int value)
{
    ChecksumEncoder::writeVInt(value);
    ensureCapacity(5);
    _bitIdx = 0;

    if (value >= 0 && value >= 64)
    {
        if (value >= 0x2000)
        {
            if (value >= 0x100000)
            {
                if (value >= 0x8000000)
                {
                    _buffer[_offset++] = (uint8_t)((value & 0x3F) | 0x80);
                    _buffer[_offset++] = (uint8_t)(((value >> 6) & 0x7F) | 0x80);
                    _buffer[_offset++] = (uint8_t)(((value >> 13) & 0x7F) | 0x80);
                    _buffer[_offset++] = (uint8_t)(((value >> 20) & 0x7F) | 0x80);
                    _buffer[_offset++] = (uint8_t)((value >> 27) & 0xF);
                }
                else
                {
                    _buffer[_offset++] = (uint8_t)((value & 0x3F) | 0x80);
                    _buffer[_offset++] = (uint8_t)(((value >> 6) & 0x7F) | 0x80);
                    _buffer[_offset++] = (uint8_t)(((value >> 13) & 0x7F) | 0x80);
                    _buffer[_offset++] = (uint8_t)((value >> 20) & 0x7F);
                }
            }
            else
            {
                _buffer[_offset++] = (uint8_t)((value & 0x3F) | 0x80);
                _buffer[_offset++] = (uint8_t)(((value >> 6) & 0x7F) | 0x80);
                _buffer[_offset++] = (uint8_t)((value >> 13) & 0x7F);
            }
        }
        else
        {
            _buffer[_offset++] = (uint8_t)((value & 0x3F) | 0x80);
            _buffer[_offset++] = (uint8_t)((value >> 6) & 0x7F);
        }
    }
    else if (value >= 0)
    {
        _buffer[_offset++] = (uint8_t)(value & 0x3F);
    }
    else if (value <= -0x40 && value <= -0x2000)
    {
        if (value <= -0x100000)
        {
            if (value <= -0x8000000)
            {
                _buffer[_offset++] = (uint8_t)((value & 0x3F) | 0xC0);
                _buffer[_offset++] = (uint8_t)(((value >> 6) & 0x7F) | 0x80);
                _buffer[_offset++] = (uint8_t)(((value >> 13) & 0x7F) | 0x80);
                _buffer[_offset++] = (uint8_t)(((value >> 20) & 0x7F) | 0x80);
                _buffer[_offset++] = (uint8_t)((value >> 27) & 0xF);
            }
            else
            {
                _buffer[_offset++] = (uint8_t)((value & 0x3F) | 0xC0);
                _buffer[_offset++] = (uint8_t)(((value >> 6) & 0x7F) | 0x80);
                _buffer[_offset++] = (uint8_t)(((value >> 13) & 0x7F) | 0x80);
                _buffer[_offset++] = (uint8_t)((value >> 20) & 0x7F);
            }
        }
        else
        {
            _buffer[_offset++] = (uint8_t)((value & 0x3F) | 0xC0);
            _buffer[_offset++] = (uint8_t)(((value >> 6) & 0x7F) | 0x80);
            _buffer[_offset++] = (uint8_t)((value >> 13) & 0x7F);
        }
    }
    else if (value <= -0x40)
    {
        _buffer[_offset++] = (uint8_t)((value & 0x3F) | 0xC0);
        _buffer[_offset++] = (uint8_t)((value >> 6) & 0x7F);
    }
    else
    {
        _buffer[_offset++] = (uint8_t)((value & 0x3F) | 0x40);
    }

    return value;
}

void ByteStream::writeLongLong(LogicLong value)
{
    ChecksumEncoder::writeLongLong(value);
    writeIntToByteArray(value.GetHigherInt());
    writeIntToByteArray(value.GetLowerInt());
}

bool ByteStream::isByteStream()
{
    return true;
}

std::string ByteStream::readStringReference(int maxCapacity)
{
    int len = readIntInternal();
    if (len <= -1 || len > maxCapacity) return "";
    std::string value((char*)(_buffer + _offset), len);
    _offset += len;
    return value;
}

std::string ByteStream::readString(int maxCapacity)
{
    int len = readIntInternal();
    if (len <= -1 || len > maxCapacity) return "";
    std::string value((char*)(_buffer + _offset), len);
    _offset += len;
    return value;
}

bool ByteStream::readBoolean()
{
    if (_bitIdx == 0) ++_offset;
    bool value = (_buffer[_offset - 1] & (1 << _bitIdx)) != 0;
    _bitIdx = (_bitIdx + 1) & 7;
    return value;
}

int ByteStream::readInt()
{
    return readIntInternal();
}

int ByteStream::readVInt()
{
    _bitIdx = 0;
    int value = 0;
    uint8_t byteValue = _buffer[_offset++];

    if ((byteValue & 0x40) != 0)
    {
        value |= byteValue & 0x3F;
        if ((byteValue & 0x80) == 0) return (int)(value | 0xFFFFFFC0);
        value |= ((byteValue = _buffer[_offset++]) & 0x7F) << 6;
        if ((byteValue & 0x80) == 0) return (int)(value | 0xFFFFE000);
        value |= ((byteValue = _buffer[_offset++]) & 0x7F) << 13;
        if ((byteValue & 0x80) == 0) return (int)(value | 0xFFF00000);
        value |= ((byteValue = _buffer[_offset++]) & 0x7F) << 20;
        if ((byteValue & 0x80) == 0) return (int)(value | 0xF8000000);
        value |= (_buffer[_offset++] & 0x7F) << 27;
        return (int)(value | 0x80000000);
    }

    value |= byteValue & 0x3F;
    if ((byteValue & 0x80) == 0) return value;
    value |= ((byteValue = _buffer[_offset++]) & 0x7F) << 6;
    if ((byteValue & 0x80) == 0) return value;
    value |= ((byteValue = _buffer[_offset++]) & 0x7F) << 13;
    if ((byteValue & 0x80) == 0) return value;
    value |= ((byteValue = _buffer[_offset++]) & 0x7F) << 20;
    if ((byteValue & 0x80) != 0) value |= (_buffer[_offset++] & 0x7F) << 27;
    return value;
}

LogicLong ByteStream::readLongLong()
{
    int higherInt = readIntInternal();
    int lowerInt = readIntInternal();
    return LogicLong(higherInt, lowerInt);
}

LogicLong ByteStream::readLong()
{
    return LogicLong(0, 0).Decode(*this);
}

void ByteStream::writeBytesWithoutLength(uint8_t* value, int length)
{
    ChecksumEncoder::writeBytes(value, length);
    if (value == nullptr) return;
    ensureCapacity(length);
    std::memcpy(_buffer + _offset, value, length);
    _offset += length;
}

int ByteStream::readBytesLength()
{
    return readIntInternal();
}

uint8_t* ByteStream::readBytes(int length, int maxCapacity)
{
    _bitIdx = 0;
    if (length <= -1 || length > maxCapacity) return nullptr;
    uint8_t* array = new uint8_t[length];
    std::memcpy(array, _buffer + _offset, length);
    _offset += length;
    return array;
}

uint8_t ByteStream::readByte()
{
    _bitIdx = 0;
    return _buffer[_offset++];
}

short ByteStream::readShort()
{
    _bitIdx = 0;
    return (short)((_buffer[_offset++] << 8) | _buffer[_offset++]);
}

void ByteStream::writeLong(LogicLong value)
{
    value.Encode(*this);
}

int ByteStream::readIntInternal()
{
    _bitIdx = 0;
    return (_buffer[_offset++] << 24) | (_buffer[_offset++] << 16) | (_buffer[_offset++] << 8) | _buffer[_offset++];
}

void ByteStream::writeIntToByteArray(int value)
{
    ensureCapacity(4);
    _bitIdx = 0;
    _buffer[_offset++] = (uint8_t)(value >> 24);
    _buffer[_offset++] = (uint8_t)(value >> 16);
    _buffer[_offset++] = (uint8_t)(value >> 8);
    _buffer[_offset++] = (uint8_t)value;
}

void ByteStream::writeVLong(LogicLong value)
{
    writeVInt(value.GetHigherInt());
    writeVInt(value.GetLowerInt());
}

long ByteStream::readVLong()
{
    int high = readVInt();
    int low = readVInt();
    return ((long)high << 32) | (uint32_t)low;
}

void ByteStream::ensureCapacity(int capacity)
{
    if (_offset + capacity <= _bufferSize) return;
    int newSize = _bufferSize + capacity + 100;
    uint8_t* tmpBuffer = new uint8_t[newSize];
    std::memcpy(tmpBuffer, _buffer, _bufferSize);
    delete[] _buffer;
    _buffer = tmpBuffer;
    _bufferSize = newSize;
}

int ByteStream::getOffset()
{
    return _offset;
}

void ByteStream::setByteArray(uint8_t* buffer, int length)
{
    _offset = 0;
    _bitIdx = 0;
    _buffer = buffer;
    _length = length;
}

void ByteStream::resetOffset()
{
    _offset = 0;
    _bitIdx = 0;
}

int ByteStream::getLength()
{
    return _offset < _length ? _length : _offset;
}

uint8_t* ByteStream::getByteArray()
{
    return _buffer;
}