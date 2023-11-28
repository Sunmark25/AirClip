#include <fstream>
#include "Device.h"
#include "ClipboardEntry.h"

std::string Device::findDevice(const std::string &deviceName, const std::string &userID){
    std::string query = "SELECT deviceID FROM Device WHERE deviceName = '" + deviceName + "' AND userID = '" + userID + "';";

    std::vector<std::vector<std::string>> tableData = dbc->selectData(query);

    if (!DatabaseController::tableIsEmpty(tableData)) {
        std::string deviceID = tableData[0][0];

        std::cout << "Device ID: " << deviceID << std::endl;

        return deviceID;
    } else { // Otherwise, return an empty string
        std::cout << "No match for device name and user id" << std::endl;

        return "";
    }
}


std::string Device::registerDevice(const std::string &deviceName, const std::string &userID){
    std::string query = "INSERT INTO Device ('deviceName', 'userID') VALUES ('" + deviceName + "', '" + userID + "');";

    bool success = dbc->sqlOperation(query);

    if (success) {
        std::cout << "Success" << std::endl;
        deviceInfo->setDeviceName(deviceName);
        return findDevice(deviceName, userID);
    } else { // Otherwise, return an empty string
        std::cout << "Unable to add a new device in the database" << std::endl;
        return "";
    }
}