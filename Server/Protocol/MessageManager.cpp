#include "headers/MessageManager.h"
#include <iostream>
#include <ostream>
#include "../../Logic/Messages/Server/Auth/headers/LoginOkMessage.h"

#include "../../Logic/Messages/Client/Auth/headers/LoginMessage.h"
#include "../../Logic/Messages/Server/Home/headers/OwnHomeDataMessage.h"
#include "../../Titan/Message/headers/PiranhaMessage.h"
#include "headers/Messaging.h"

MessageManager::MessageManager(Messaging* messaging)
    : messaging(messaging) { }

void MessageManager::handleMessage(PiranhaMessage* message) {
    switch (message->getMessageType()) {
        case 10101:
            handleClientHelloMessage(static_cast<LoginMessage*>(message));
    }
}

void MessageManager::handleClientHelloMessage(LoginMessage* message) {
    std::cout << "received loginMessage" << std::endl;
    MessageManager::sendMessage(new LoginOkMessage());
    MessageManager::sendMessage(new OwnHomeDataMessage());
}

void MessageManager::sendMessage(PiranhaMessage* message) {
    if (messaging) {
        messaging->send(message);
    }
}