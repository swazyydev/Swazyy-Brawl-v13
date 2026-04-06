#pragma once
#include "../../../../../Titan/Message/headers/PiranhaMessage.h"

class LoginMessage : public PiranhaMessage {
public:
    LoginMessage();

    void decode() override;
    int getMessageType() override;
    int getServiceNodeType() override;
};