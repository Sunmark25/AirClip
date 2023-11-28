#ifndef DEVICE_H
#define DEVICE_H

#include <string>
#include <vector>
#include <thread>
#include "DeviceInfo.h"
#include "DatabaseController.h"

// Forward declaration of the DeviceInfo and ClipboardEntry classes
class DeviceInfo;
class ClipboardEntry;

class Device {
private:
    DatabaseController *dbc;
    DeviceInfo *deviceInfo;
    std::vector<int> clipboardEntryIds;

public:
    /**
     * The constructor for Device which takes the wtConnectionId and binds the deviceInfo to device
     *
     * @param wtConnectionId The corresponding wt connection ID (for device's web page) for the device
     */
    explicit Device(const std::string &wtConnectionId) {
        deviceInfo = new DeviceInfo("", wtConnectionId, "", "");
        dbc = DatabaseController::getInstance("");
    }

    std::string findDevice(const std::string &deviceName, const std::string &userID);

    std::string registerDevice(const std::string &deviceName, const std::string &userID);
};

#endif // DEVICE_H
