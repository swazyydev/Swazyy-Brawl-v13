#include "headers/ByteStreamHelper.h"

void ByteStreamHelper::writeDataReference(ByteStream& stream, int high, int low) {
    stream.writeVInt(high);
    stream.writeVInt(low);
}

void ByteStreamHelper::encodeIntList(ByteStream& stream, std::vector<int> list) {
    int length = list.size();
    stream.writeVInt(length);
    for (auto i : list) {
        stream.writeVInt(i);
    }
}
