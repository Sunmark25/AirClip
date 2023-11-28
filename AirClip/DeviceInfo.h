#ifndef DEVICEINFO_H
#define DEVICEINFO_H

#include <string>


/**
 * @class DeviceInfo
 * @brief Represents information about a device.
 *
 * This class encapsulates various details about a device, such as its unique device ID, connection ID, name, and network address.
 */
class DeviceInfo {
private:
    std::string deviceId;        ///< Unique identifier for the device.
    std::string deviceName;      ///< Human-readable name of the device.
    std::string networkAddress;  ///< Network address of the device.

public:

/**
     * @brief Constructs a new DeviceInfo object.
     *
     * Initializes a new instance of the DeviceInfo class with specified device information.
     *
     * @param deviceId The unique identifier for the device.
     * @param wtConnectionId The identifier for the device's connection.
     * @param deviceName The human-readable name of the device.
     * @param networkAddress The network address of the device.
     */
    DeviceInfo(const std::string &deviceId, const std::string &deviceName, const std::string &networkAddress){
        this->deviceId = deviceId;
        this->deviceName = deviceName;
        this->networkAddress = networkAddress;
    }

    std::string getDeviceId() const;         ///< Returns the device's unique identifier.
    std::string getDeviceName() const;       ///< Returns the device's human-readable name.
    std::string getNetworkAddress() const;   ///< Returns the network address of the device.

    void setDeviceId(const std::string &value);          ///< Sets the device's unique identifier.
    void setDeviceName(const std::string &value);        ///< Sets the device's human-readable name.
    void setNetworkAddress(const std::string &value);    ///< Sets the network address of the device.

    bool updateDeviceInfo(const DeviceInfo& newInfo);

};

#endif // DEVICEINFO_H
