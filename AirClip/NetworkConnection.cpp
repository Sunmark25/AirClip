/**
 * @class NetworkConnection
 * @brief Manages network connections for a server-client architecture.
 *
 * This class handles network-related functionalities such as starting a server,
 * accepting client connections, and performing data read and write operations over the network.
 * It uses socket programming to establish and manage TCP connections.
 */

#include "NetworkConnection.h"


/**
    * @brief Constructor for NetworkConnection.
    *
    * Initializes a new NetworkConnection instance. Sets up a socket for the server
    * using the given IP address and port. If socket creation fails, the program will terminate.
    *
    * @param ipAddress The IP address of the server.
    * @param port The port number on which the server will listen for connections.
    */
NetworkConnection::NetworkConnection(const std::string &ipAddress, int port)
        : ipAddress(ipAddress), port(port), addrlen(sizeof(address)) {
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }
}

/**
    * @brief Destructor for NetworkConnection.
    *
    * Closes the server's file descriptor to properly release the network resources.
    */
NetworkConnection::~NetworkConnection() {
    close(server_fd);
}

/**
     * @brief Starts the server.
     *
     * Sets socket options, binds the server to the given address and port, and starts listening for incoming connections.
     * @return bool True if the server starts successfully, false if any step fails.
     */
bool NetworkConnection::startServer() {
    int opt = 1;
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt))) {
        perror("setsockopt");
        return false;
    }
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(port);

    if (bind(server_fd, (struct sockaddr*)&address, sizeof(address)) < 0) {
        perror("bind failed");
        return false;
    }
    if (listen(server_fd, 3) < 0) {
        perror("listen");
        return false;
    }
    runningServer = true;
    return true;
}

/**
     * @brief Accepts a new client connection.
     *
     * Accepts an incoming client connection request and establishes a connection.
     * @return bool True if the connection is successfully accepted, false otherwise.
     */
bool NetworkConnection::acceptConnection() {
    if ((new_socket = accept(server_fd, (struct sockaddr*)&address, &addrlen)) < 0) {
        perror("accept");
        return false;
    }
    return true;
}

/**
     * @brief Reads data from the connected client.
     *
     * Reads data sent by the client into the provided buffer.
     * @param buffer The buffer to store the read data.
     * @param bufferSize The size of the buffer.
     * @return bool True if data is successfully read, false otherwise.
     */
bool NetworkConnection::readData(char* buffer, size_t bufferSize) {
    ssize_t valread = read(new_socket, buffer, bufferSize - 1);
    if (valread < 0) {
        perror("read");
        return false;
    }
    buffer[valread] = '\0';
    return true;
}

/**
     * @brief Sends data to the connected client.
     *
     * Sends the specified data to the client.
     * @param data The data to be sent.
     * @return bool True if the data is successfully sent, false otherwise.
     */
bool NetworkConnection::sendData(const char* data) {
    if (send(new_socket, data, strlen(data), 0) < 0) {
        perror("send");
        return false;
    }
    return true;
}

/**
     * @brief Closes the connection with the client.
     *
     * Closes the client's socket, effectively terminating the connection.
     */
void NetworkConnection::closeConnection() {
    close(new_socket);
}
