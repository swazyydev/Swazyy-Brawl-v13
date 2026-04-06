#pragma once
#include "../../../../../Titan/Message/headers/PiranhaMessage.h"
#include "../../../../Avatar/headers/LogicClientAvatar.h"
#include "../../../../Home/headers/LogicClientHome.h"

class OwnHomeDataMessage : public PiranhaMessage {
private:
    LogicClientHome clientHome;
    LogicClientAvatar clientAvatar;
public:
    OwnHomeDataMessage();

    void encode() override;
    int getMessageType() override;
    int getServiceNodeType() override;
};
