/**
 * @class AirClipServer
 * @brief Handles server operations for the AirClip application.
 * @authors Benz, Jarrett
 * This class is responsible for managing server-side functionalities for the AirClip application.
 * It includes methods for starting and stopping the server, handling new connections, and performing
 * user authentication and registration. The class utilizes a `NetworkConnection` object for network
 * communication and a `UserManager` object for user management.
 *
 * @note The implementation details for the start and stop server methods are currently not provided.
 */

#include "AirClipServer.h"

/**
     * @brief Starts the AirClip server.
     *
     * Initializes and starts the server on a specified port. Listens for incoming connections and handles
     * data communication with connected clients. It also logs server activity to the console.
     */
void AirClipServer::startServer() {
    std::cout << "Starting Server..." << std::endl;

    NetworkConnection server("0.0.0.0", 8080);
    if (!server.startServer()) {
        fprintf(stderr, "Failed to start server\n");
        exit(EXIT_FAILURE);
    }

    // Used to test the newConnection class and children classes
    // newConnection("");

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

/**
     * @brief Stops the AirClip server.
     *
     * Currently, the implementation details for this method are not provided in the given code snippet.
     */
void AirClipServer::stopServer() {

}

/**
    * @brief Handles a new connection from a client.
    *
    * Manages new connections by authenticating existing users or registering new users. The method uses the
    * provided Wt connection ID, and credentials to interact with the UserManager for authentication and
    * registration processes.
    *
    * @param wtConnectionId The connection ID provided by the Wt framework for the client.
    */
void AirClipServer::newConnection(const std::string &wtConnectionId) {
    // Used to store the username and password for testing
    // This will have to be received from the client
    const std::string username = "tmikgree";
    const std::string password = "password123";
    const std::string fullName = "Test MikGee";

    // Get the user's name from the database if it exists
    std::string newUserId = userManager->findUser(username);

    // If the user's ID is not empty then try to authenticate them
    if (!newUserId.empty()) {
        // Try to authenticate the user, if their credentials are correct this will be true
        bool authenticated = userManager->authenticateUser(username,password);

        // If the user was authenticated then finish logging them in
        if (authenticated) {
            std::cout << "User authenticated" << std::endl;

            // Call finishUserLogIn to finish logging the user in
            userManager->finishUserLogIn(newUserId, wtConnectionId, username);
        } else { // Otherwise, if they weren't...
            std::cout << "Invalid username and password given" << std::endl;
            // Inform the user
        }
    } else { // Otherwise, if the user couldn't be found then register a new user and log them in
        // Register a new user using the username and password
        std::string registeredUsersId = userManager->registerUser(username,password, fullName);

        // Call finishUserLogIn to finish logging the user in
        userManager->finishUserLogIn(registeredUsersId, wtConnectionId, username);
    }
}

/**
 * @brief Entry point for the AirClip server application.
 *
 * Instantiates an AirClipServer object and starts the server.
 */
int main(){
    AirClipServer airClipServer;
    airClipServer.startServer();
}

