#include "headers/LogicConfData.h"
#include "../../Titan/DataSteam/headers/ByteStream.h"
#include "../../Titan/DataSteam/headers/ByteStreamHelper.h"

void LogicConfData::encode(ByteStream& stream) {
    stream.writeVInt(0);
    stream.writeVInt(100);
    stream.writeVInt(10);
    stream.writeVInt(30);
    stream.writeVInt(3);
    stream.writeVInt(80);
    stream.writeVInt(10);
    stream.writeVInt(40);
    stream.writeVInt(1000);
    stream.writeVInt(550);
    stream.writeVInt(0);
    stream.writeVInt(999900);

    ByteStreamHelper::encodeIntList(stream, std::vector<int> { 0, 30, 80, 170, 350, 0 });

    stream.writeVInt(4);
    for (int i = 0; i < 4; i++) {
        stream.writeVInt(i + 1);
    }

    stream.writeVInt(4);
    for (int i = 0; i < 4; i++) {
        stream.writeVInt(0);
        stream.writeVInt(i + 1);
        stream.writeVInt(0);
        stream.writeVInt(0);
        stream.writeVInt(0);
        ByteStreamHelper::writeDataReference(stream, 15, 7);
        stream.writeVInt(0);
        stream.writeString("");
        stream.writeVInt(0);
        stream.writeVInt(0);
        stream.writeVInt(0);
    }

    stream.writeVInt(0);

    ByteStreamHelper::encodeIntList(stream, std::vector<int> { 20, 35, 75, 140, 290, 480, 800, 1250 });
    ByteStreamHelper::encodeIntList(stream, std::vector<int> { 1, 2, 3, 4, 5, 10, 15, 20 });
    ByteStreamHelper::encodeIntList(stream, std::vector<int> { 10, 30, 80 });
    ByteStreamHelper::encodeIntList(stream, std::vector<int> { 6, 20, 60 });
    ByteStreamHelper::encodeIntList(stream, std::vector<int> { 20, 50, 140 });
    ByteStreamHelper::encodeIntList(stream, std::vector<int> { 150, 400, 1200 });

    stream.writeVInt(0);
    stream.writeVInt(200);
    stream.writeVInt(20);
    stream.writeVInt(8640);
    stream.writeVInt(10);
    stream.writeVInt(5);

    stream.writeBoolean(false);
    stream.writeBoolean(false);
    stream.writeBoolean(false);

    stream.writeVInt(0);
    stream.writeVInt(0);

    stream.writeBoolean(true);

    stream.writeVInt(0);
}
