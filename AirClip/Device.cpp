/**
 * @class Device
 * @brief Manages device-related operations in a database.
 *
 * The Device class encapsulates functionalities for interacting with a database
 * to manage device records. It provides methods to find and register devices,
 * linking them with user accounts. The class assumes the existence of a database
 * connection through a DatabaseController instance and operates SQL queries to
 * manage device data.
 *
 * Key functionalities include:
 *   - Searching for a device based on its name and user ID.
 *   - Registering a new device in the database with a given name and user ID.
 *
 * @note The class uses SQL queries to interact with the database and provides feedback
 *       through console messages indicating the success or failure of database operations.
 */
#include <fstream>
#include "Device.h"
#include "ClipboardEntry.h"


/**
 * @brief Searches for a device in the database based on its name and associated user ID.
 *
 * This method constructs and executes an SQL query to find a device in the database
 * matching the provided device name and user ID. If a matching device is found, its ID is returned.
 *
 * @param deviceName The name of the device to search for.
 * @param userID The ID of the user associated with the device.
 * @return std::string The ID of the found device; returns an empty string if no match is found.
 *
 * @note Logs the device ID to the console if a match is found or a message indicating no match if not.
 */
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

/**
 * @brief Registers a new device in the database.
 *
 * This method inserts a new device into the database using the provided device name and user ID.
 * Upon successful insertion, it sets the device name in the deviceInfo instance and then searches
 * for the device in the database to obtain and return its ID.
 *
 * @param deviceName The name of the device to register.
 * @param userID The ID of the user associated with the device.
 * @return std::string The ID of the newly registered device if successful; an empty string otherwise.
 *
 * @note Logs a success message to the console upon successful insertion or an error message if the insertion fails.
 */
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