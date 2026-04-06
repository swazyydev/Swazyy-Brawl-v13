#pragma once
#include "../../../../../Titan/Message/headers/PiranhaMessage.h"

class LoginOkMessage : public PiranhaMessage {
public:
    LoginOkMessage();

    void encode() override;
    int getMessageType() override;
    int getServiceNodeType() override;
};