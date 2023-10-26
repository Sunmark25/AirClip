#include <iostream>
#include "AirClipServer.h"


void AirClipServer::startServer() {
    NetworkConnection server("0.0.0.0", 8080);
    if (!server.startServer()) {
        fprintf(stderr, "Failed to start server\n");
        exit(EXIT_FAILURE);
    }

    while (true) {
        if (server.acceptConnection()) {
            char buffer[1024] = { 0 };
            if (server.readData(buffer, sizeof(buffer))) {
                printf("%s\n", buffer);
            }
            server.sendData("Hello from server");
            server.closeConnection();

        }
    }
}

void AirClipServer::stopServer() {

}

void AirClipServer::newConnection(std::string wtConnectionId) {

}

int main(){
    std::cout << "eee" << std::endl;
    AirClipServer airClipServer;
    airClipServer.startServer();
}


/*
UserManager AirClipServer::userManager() {
}
 */

