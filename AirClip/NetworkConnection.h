#ifndef NETWORKCONNECTION_H
#define NETWORKCONNECTION_H

#include <string>
#include <vector>
//#include "Device.h" // Include the appropriate header for the Device class
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include <string>


class NetworkConnection {
public:
    NetworkConnection(const std::string &ipAddress, int port);
    ~NetworkConnection();
    bool startServer();
    bool acceptConnection();
    bool readData(char* buffer, size_t bufferSize);
    bool sendData(const char* data);
    void closeConnection();

    // std::vector<Device> scanNetwork();
    bool runningServer;

private:
    int server_fd, new_socket;
    struct sockaddr_in address;
    socklen_t addrlen;
    std::string ipAddress;
    int port;
};

#endif // NETWORKCONNECTION_H
