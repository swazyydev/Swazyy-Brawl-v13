#pragma once
#include "../../Data/headers/LogicConfData.h"
#include "../../Data/headers/LogicDailyData.h"

class ByteStream;
class ByteStreamHelper;

class LogicClientHome {
private:
    LogicDailyData dailyData;
    LogicConfData confData;
public:
    void encode(ByteStream& stream);
};
