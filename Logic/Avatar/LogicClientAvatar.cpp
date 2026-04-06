#include "headers/LogicClientAvatar.h"
#include "../../Titan/DataSteam/headers/ByteStream.h"

void LogicClientAvatar::encode(ByteStream& stream) {
    stream.writeVLong(LogicLong(1, 0));
    stream.writeVLong(LogicLong(1, 0));
    stream.writeVLong(LogicLong(1, 0));

    stream.writeStringReference("t.me/spookyswazyy");
    stream.writeBoolean(true);
    stream.writeInt(0);

    stream.writeVInt(8);

    stream.writeVInt(0);
    stream.writeVInt(0);
    stream.writeVInt(0);
    stream.writeVInt(0);
    stream.writeVInt(0);
    stream.writeVInt(0);
    stream.writeVInt(0);
    stream.writeVInt(0);

    stream.writeVInt(0);
    stream.writeVInt(0);
    stream.writeVInt(0);
    stream.writeVInt(0);
    stream.writeVInt(0);
    stream.writeVInt(0);
    stream.writeVInt(0);
    stream.writeVInt(0);
    stream.writeVInt(0);
    stream.writeVInt(0);
    stream.writeVInt(2);
}