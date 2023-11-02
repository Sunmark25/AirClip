//
// Created by Tingrui Zhang on 2023-10-25.
//

#include "NetworkConnection.h"



NetworkConnection::NetworkConnection(const std::string &ipAddress, int port)
        : ipAddress(ipAddress), port(port), addrlen(sizeof(address)) {
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }
}

NetworkConnection::~NetworkConnection() {
    close(server_fd);
}

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

bool NetworkConnection::acceptConnection() {
    if ((new_socket = accept(server_fd, (struct sockaddr*)&address, &addrlen)) < 0) {
        perror("accept");
        return false;
    }
    return true;
}

bool NetworkConnection::readData(char* buffer, size_t bufferSize) {
    ssize_t valread = read(new_socket, buffer, bufferSize - 1);
    if (valread < 0) {
        perror("read");
        return false;
    }
    buffer[valread] = '\0';
    return true;
}

bool NetworkConnection::sendData(const char* data) {
    if (send(new_socket, data, strlen(data), 0) < 0) {
        perror("send");
        return false;
    }
    return true;
}

void NetworkConnection::closeConnection() {
    close(new_socket);
}
