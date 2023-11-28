#ifndef DEVICEINFO_H
#define DEVICEINFO_H

#include <string>


class DeviceInfo {
private:
    std::string deviceId;
    std::string wtConnectionId;
    std::string deviceName;
    std::string networkAddress;

public:

    DeviceInfo(const std::string &deviceId, const std::string &wtConnectionId, const std::string &deviceName, const std::string &networkAddress){
        this->deviceId = deviceId;
        this->wtConnectionId = wtConnectionId;
        this->deviceName = deviceName;
        this->networkAddress = networkAddress;
    }

    std::string getDeviceId() const;
    std::string getWtConnectionId() const;
    std::string getDeviceName() const;
    std::string getNetworkAddress() const;

    void setDeviceId(const std::string &value);
    void setWtConnectionId(const std::string &value);
    void setDeviceName(const std::string &value);
    void setNetworkAddress(const std::string &value);

    bool updateDeviceInfo(const DeviceInfo& newInfo);

};

#endif // DEVICEINFO_H
