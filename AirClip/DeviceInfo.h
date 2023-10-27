#ifndef DEVICEINFO_H
#define DEVICEINFO_H

#include <string>

class DeviceInfo {
private:
    std::string deviceId;
    std::string wtConnectionId;
    std::string deviceType;
    std::string networkAddress;

public:
    explicit DeviceInfo(const std::string &deviceId, const std::string &wtConnectionId, const std::string &deviceType,
                        const std::string &networkAddress) {

    }

    // Getter method to retrieve device information
    [[nodiscard]] DeviceInfo getDeviceInfo() const;

    // Method to add device information
    bool addDeviceInfo(const DeviceInfo& info);

    // Method to update device information
    bool updateDeviceInfo(const DeviceInfo& newInfo);
};

#endif // DEVICEINFO_H
