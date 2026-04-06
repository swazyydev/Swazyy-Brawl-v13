#pragma once
#include <cstdint>

class PiranhaMessage;
class LoginMessage;
class Messaging;

class MessageManager {
    private:
    Messaging* messaging;

    public:
    MessageManager(Messaging* messaging);

    void handleClientHelloMessage(LoginMessage * message);

    void handleMessage(PiranhaMessage* message);

    void sendMessage(PiranhaMessage* message);
};
