#include "headers/Messaging.h"

#include <exception>
#include <iostream>
#include <ostream>

#include "../../Titan/Message/headers/PiranhaMessage.h"
#include "../../Logic/Messages/headers/LogicLaserMessageFactory.h"
#include "headers/MessageManager.h"

Messaging::Messaging(int clientSocket)
    : _clientSocket(clientSocket) {
}

void Messaging::receive() {
    try {
       while (true) {
           uint8_t header[7];
           if (!readBytes(header, 7)) return;

           ushort messageId = (header[0] << 8) | header[1];
           int payloadLength = (header[2] << 16) | (header[3] << 8) | header[4];
           ushort version = (header[5] << 8) | header[6];

           uint8_t payload[payloadLength];
           if (!readBytes(payload, payloadLength)) return;

           std::cout << "Received message with type=" << messageId << std::endl;

           LogicLaserMessageFactory factory;
           PiranhaMessage* msg = factory.createMessageByType(messageId);
           if (!msg) {
               std::cout << "Unknown message type: " << messageId << std::endl;
               return;
           }

           msg->version = version;
           msg->_stream.setByteArray(payload, payloadLength);
           msg->_stream.resetOffset();
           msg->decode();

           MessageManager messageManager(this);
           messageManager.handleMessage(msg);
       }
    }
    catch (std::exception& e) {
        std::cout << "Exception : " << e.what() << std::endl;
    }
}

void Messaging::send(PiranhaMessage* message) {
    if (!message) return;

    message->encode();
    uint8_t* payload = message->_stream.getByteArray();
    int payloadLength = message->_stream.getLength();

    uint8_t header[7];
    header[0] = (message->getMessageType() >> 8);
    header[1] = message->getMessageType();

    header[2] = (payloadLength >> 16);
    header[3] = (payloadLength >> 8);
    header[4] = payloadLength;

    header[5] = (message->version >> 8);
    header[6] = message->version;

    int sent = 0;
    while (sent < 7) {
        int bytesSent = ::send(_clientSocket, header + sent, 7 - sent, 0);
        if (bytesSent <= 0) return;
        sent += bytesSent;
    }

    sent = 0;
    while (sent < payloadLength) {
        int bytesSent = ::send(_clientSocket, payload + sent, payloadLength - sent, 0);
        if (bytesSent <= 0) return;
        sent += bytesSent;
    }

    std::cout << "Sent message with type=" << message->getMessageType() << std::endl;
}

bool Messaging::readBytes(uint8_t* bytes, int length) {
    int total = 0;
    while (total < length) {
        int byteRead = recv(_clientSocket, bytes + total, length - total, 0);
        if (byteRead <= 0) return false;
        total += byteRead;
    }
    return true;
}