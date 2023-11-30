#ifndef DEVICE_H
#define DEVICE_H

#include <string>
#include <vector>
#include <thread>
#include <Wt/WApplication.h>
#include "DeviceInfo.h"
#include "DatabaseController.h"
#include "UI.h"

// Forward declaration of the DeviceInfo and ClipboardEntry classes
class DeviceInfo;
class ClipboardEntry;

class Device {
private:
    DatabaseController *dbc; ///< Pointer to the DatabaseController instance for database operations.
    DeviceInfo *deviceInfo; ///< Pointer to the DeviceInfo instance for storing device-specific information.
    std::vector<int> clipboardEntryIds; ///< Vector of clipboard entry IDs associated with the device.

public:
    /**
     * @brief Constructor for Device.
     *
     * Initializes a Device object by creating a DeviceInfo instance and obtaining a DatabaseController instance.
     *
     * @param wtConnectionId The Wt connection ID associated with the device's web page.
     */
    explicit Device() {
        deviceInfo = new DeviceInfo("", "", "", "");
        dbc = DatabaseController::getInstance();
    }

    std::string findDevice(const std::string &deviceName, const std::string &userID);

    std::string registerDevice(const std::string &deviceName, const std::string &userID);

    std::unique_ptr<Wt::WApplication> associateWithSession(const Wt::WEnvironment &env);

    DeviceInfo* getDeviceInfo();
};

#endif // DEVICE_H
