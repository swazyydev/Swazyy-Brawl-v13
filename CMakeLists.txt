cmake_minimum_required(VERSION 4.2)
project(swazyy_core)

set(CMAKE_CXX_STANDARD 20)

add_executable(swazyy_core main.cpp
        Server/Network/tcpserver.cpp
        Server/Network/headers/tcpserver.h
        Server/Protocol/Messaging.cpp
        Server/Protocol/headers/Messaging.h
        Server/Protocol/MessageManager.cpp
        Server/Protocol/headers/MessageManager.h
        Titan/Message/PiranhaMessage.cpp
        Titan/Message/headers/PiranhaMessage.h
        Titan/DataSteam/ChecksumEncoder.cpp
        Titan/DataSteam/headers/ChecksumEncoder.h
        Titan/Maths/LogicLong.cpp
        Titan/Maths/headers/LogicLong.h
        Titan/DataSteam/ByteStream.cpp
        Titan/DataSteam/headers/ByteStream.h
        Logic/Messages/LogicLaserMessageFactory.cpp
        Logic/Messages/headers/LogicLaserMessageFactory.h
        Logic/Messages/Client/Auth/LoginMessage.cpp
        Logic/Messages/Client/Auth/headers/LoginMessage.h
        Logic/Messages/Server/Auth/LoginOkMessage.cpp
        Logic/Messages/Server/Auth/headers/LoginOkMessage.h
        Logic/Messages/Server/Home/OwnHomeDataMessage.cpp
        Logic/Messages/Server/Home/headers/OwnHomeDataMessage.h
        Logic/Avatar/LogicClientAvatar.cpp
        Logic/Avatar/headers/LogicClientAvatar.h
        Logic/Data/LogicDailyData.cpp
        Logic/Data/headers/LogicDailyData.h
        Logic/Data/LogicConfData.cpp
        Logic/Data/headers/LogicConfData.h
        Logic/Home/LogicClientHome.cpp
        Logic/Home/headers/LogicClientHome.h
        Titan/DataSteam/ByteStreamHelper.cpp
        Titan/DataSteam/headers/ByteStreamHelper.h)
