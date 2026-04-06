#pragma once
#include <cstdint>
#include "../../../Titan/Message/headers/PiranhaMessage.h"

class Messaging {
private:
    int _clientSocket;

public:
    Messaging(int clientSocket);

    void receive();
    void send(PiranhaMessage* message);

private:
    bool readBytes(uint8_t* bytes, int length);
};