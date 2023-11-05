#ifndef DEVICEINFO_H
#define DEVICEINFO_H

#include <string>
using namespace std;


class DeviceInfo {
private:
    string deviceId;
    string wtConnectionId;
    string deviceType;
    string networkAddress;

public:

    DeviceInfo(const string &deviceId, const string &wtConnectionId, const string &deviceType, const string &networkAddress){
        this->deviceId = deviceId;
        this->wtConnectionId = wtConnectionId;
        this->deviceType = deviceType;
        this->networkAddress = networkAddress;
    }

    std::string getDeviceId() const;
    std::string getWtConnectionId() const;
    std::string getDeviceType() const;
    std::string getNetworkAddress() const;

    void setDeviceId(const std::string &value);
    void setWtConnectionId(const std::string &value);
    void setDeviceType(const std::string &value);
    void setNetworkAddress(const std::string &value);

    bool updateDeviceInfo(const DeviceInfo& newInfo);

};

#endif // DEVICEINFO_H
