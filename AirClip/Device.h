#ifndef DEVICE_H
#define DEVICE_H

#include <string>
#include <vector>
#include <thread>
#include "DeviceInfo.h"

// Forward declaration of the DeviceInfo and ClipboardEntry classes
class DeviceInfo;
class ClipboardEntry;

class Device {
private:
    DeviceInfo deviceInfo;
    std::vector<int> clipboardEntryIds;

    // Method to synchronize clipboard content to the device
    void syncClipboardToDevice(const ClipboardEntry& content);

    // Method to download a file associated with a clipboard entry
    bool downloadFile(int clipboardEntryId);

    bool sendToServer(std::ifstream file);

    // Private method to perform device-specific actions
    void performActions();

    // Private method to notify the user interface
    void notifyUI();

    // Private method to listen to user interface events
    void listenToUI();

public:
    explicit Device(std::string wtConnectionId);

    Device::Device(std::string wtConnectionId) {

    }

    // Method to connect the device to a server
    bool connectToServer();

    // Method to synchronize clipboard content from the device
    ClipboardEntry syncClipboardFromDevice();

    // Method to add the device
    void addDevice();

    // Method to remove the device
    void removeDevice();

    // Method to create a thread for the device
    std::thread createThread();

};

#endif // DEVICE_H
