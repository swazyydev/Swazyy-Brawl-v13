#pragma once
#include "ByteStream.h"

class ByteStreamHelper {
    public:
    static void writeDataReference(ByteStream& stream, int high, int low);
    static void encodeIntList(ByteStream& stream, std::vector<int> list);
};
