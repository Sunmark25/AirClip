#include <iostream>
#include "AirClipServer.h"

void AirClipServer::startServer() {
    std::cout << "Starting Server..." << std::endl;

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

void AirClipServer::newConnection(const std::string &wtConnectionId) {
    // Used to store the username and password for testing
    // This will have to be received from the client
    const std::string username = "test";
    const std::string password = "password123";

    // Get the user's name from the database if it exists
    std::string newUserId = userManager->findUser(username);

    // If the user's ID is not empty then try to authenticate them
    if (!newUserId.empty()) {
        // Try to authenticate the user, if their credentials are correct this will be true
        bool authenticated = userManager->authenticateUser(username,password);

        // If the user was authenticated...
        if (authenticated) {
            std::cout << "User authenticated" << std::endl;

            // Call finishUserLogIn to finish logging the user in
            userManager->finishUserLogIn(newUserId, wtConnectionId, username);
        } else { // Otherwise, if they weren't...
            std::cout << "Invalid username and password given" << std::endl;
            // Inform the user
        }
    } else { // Otherwise, if the user couldn't be found register a new user
        // Register a new user using the username and password
        std::string registeredUsersId = userManager->registerUser(username,password);

        // Call finishUserLogIn to finish logging the user in
        userManager->finishUserLogIn(registeredUsersId, wtConnectionId, username);
    }
}

int main(){
    AirClipServer airClipServer;
    airClipServer.startServer();
}

