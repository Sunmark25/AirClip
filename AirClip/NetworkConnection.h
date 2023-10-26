#ifndef NETWORKCONNECTION_H
#define NETWORKCONNECTION_H

#include <string>
#include <vector>
#include "Device.h" // Include the appropriate header for the Device class

class NetworkConnection {
private:
    std::string ipAddress;

public:
    explicit NetworkConnection(const std::string& ipAddress);

    // Method to scan the network and retrieve a list of devices
    std::vector<Device> scanNetwork();
};

#endif // NETWORKCONNECTION_H
