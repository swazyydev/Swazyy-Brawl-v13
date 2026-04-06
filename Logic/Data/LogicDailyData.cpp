#include "headers/LogicDailyData.h"
#include "../../Titan/DataSteam/headers/ByteStream.h"
#include "../../Titan/DataSteam/headers/ByteStreamHelper.h"

void LogicDailyData::encode(ByteStream& stream) {
    stream.writeVInt(0);
    stream.writeVInt(0);
    stream.writeVInt(0);
    stream.writeVInt(0);
    stream.writeVInt(0);
    stream.writeVInt(1);
    stream.writeVInt(0);

    ByteStreamHelper::writeDataReference(stream, 28, 0);

    stream.writeVInt(0);

    stream.writeVInt(0);

    stream.writeVInt(0);

    stream.writeBoolean(false);
    stream.writeVInt(0);
    stream.writeVInt(0);
    stream.writeVInt(0);
    stream.writeVInt(0);
    stream.writeVInt(0);
    stream.writeVInt(0);
    stream.writeBoolean(false);
    stream.writeVInt(0);
    stream.writeBoolean(false);
    stream.writeVInt(0);
    stream.writeVInt(0);
    stream.writeBoolean(false);
    stream.writeBoolean(false);
    stream.writeBoolean(false);
    stream.writeBoolean(false);

    stream.writeVInt(0);
    stream.writeVInt(0);
    stream.writeVInt(0);

    stream.writeBoolean(false);

    stream.writeVInt(0);

    stream.writeVInt(0);

    stream.writeVInt(0);
    stream.writeVInt(0);
    stream.writeVInt(0);
    stream.writeVInt(0);

    stream.writeVInt(0);

    ByteStreamHelper::writeDataReference(stream, 16, 0);
}