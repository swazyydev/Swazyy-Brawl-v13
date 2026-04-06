#include "headers/LogicClientHome.h"
#include "../../Titan/DataSteam/headers/ByteStream.h"

#include "../Data/headers/LogicDailyData.h"

void LogicClientHome::encode(ByteStream& stream) {
    dailyData.encode(stream);
    confData.encode(stream);
    
    stream.writeLong(LogicLong(1, 0));
    stream.writeVInt(0);
    stream.writeVInt(0);
    stream.writeBoolean(false);
    stream.writeVInt(0);
}
