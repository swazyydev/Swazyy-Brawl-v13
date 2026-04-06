#include <iostream>

#include "Server/Network/headers/tcpserver.h"

int main() {
    std::cout << "Made by Swazyy with love <3" << std::endl;
    tcpserver::start(9339);
    return 0;
}
