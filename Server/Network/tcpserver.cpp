#include "headers/tcpserver.h"
#include <sys/socket.h>
#include <netinet/in.h>

#include "../Protocol/headers/Messaging.h"

void tcpserver::start(int port) {
    int listener = socket(AF_INET, SOCK_STREAM, 0);
    if (listener < 0) {
        std::cout << "Error creating socket" << std::endl;
    }

    sockaddr_in address;
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(port);

    if (bind(listener, reinterpret_cast<sockaddr *>(&address), sizeof(address)) < 0) {
        std::cout << "Bind failed" << std::endl;
    }

    if (listen(listener, 10) < 0) {
        std::cout << "Listen failed" << std::endl;
    }

    std::cout << "Server is listening on port " << port << std::endl;

    while (true) {
        sockaddr_in client;
        socklen_t clientlen = sizeof(client);

        int clientSocket = accept(listener, (struct sockaddr*) &client, &clientlen);
        if (clientSocket < 0) {
            std::cout << "Accept failed" << std::endl;
        }

        std::cout << "New connection !" << std::endl;

        Messaging messaging(clientSocket);
        messaging.receive();
    }
}
