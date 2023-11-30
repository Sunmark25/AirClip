/**
 * @class NetworkConnection
 * @brief Manages network connections for a server-client architecture.
 *
 * This class handles network-related functionalities such as starting a server,
 * accepting client connections, and performing data read and write operations over the network.
 * It uses socket programming to establish and manage TCP connections.
 */

#include "NetworkConnection.h"
#include "Device.h"
#include "DeviceInfo.h"
#include "UserManager.h"
#include "ClipboardHelper.h"

const unsigned short NetworkConnection::PORT = 4800;

void NetworkConnection::startServer() {
    std::cout << "Starting HTTP API" << std::endl;

    crow::SimpleApp app; // Define the crow application
    UserManager userManager = UserManager();

    CROW_ROUTE(app, "/api/")([]() {
        return "Welcome to the API";
    });

    // Used to receive clipboard data from the client
    // TODO: Improve, add authentication so this can't be spoofed
    // Use: `curl -d '{"content":"<string-content>","deviceID":"<int-device-id>","lastUpdatedTime":"<string-date>","username":"<username>"}' -H "Content-Type: application/json" 0.0.0.0:4800/api/clipboard/send`
    CROW_ROUTE(app, "/api/clipboard/send")
            .methods("POST"_method)([](const crow::request &req) {
                std::cout << "Raw body: " << req.body << std::endl;

                auto jsonData = crow::json::load(req.body);

                if (!jsonData) {
                    crow::response res(400); // Set HTTP status code to 400 (Bad Request)
                    res.body = "Invalid JSON"; // Set response body to the error message
                    res.set_header("Content-Type", "text/plain");
                    return res;
                }

                std::string clipboardEntryID = ClipboardHelper::insertClipboardEntry(jsonData["lastUpdatedTime"].s(), jsonData["deviceID"].s(), jsonData["content"].s(), "", "");

                // Check if clipboard entry insertion failed
                if (clipboardEntryID.empty()) {
                    crow::response res(500); // Set HTTP status code to 500 (Internal Server Error)
                    res.body = "Failed to insert clipboard entry"; // Set response body to the error message
                    res.set_header("Content-Type", "text/plain");
                    return res;
                }

                crow::response res(200);
                res.body = "Successfully insert clipboard entry";
                res.set_header("Content-Type", "text/plain");
                return res;
            });

    // TODO: Implement a websocket to listen for clipboard changes from the server
    // https://stackoverflow.com/a/12442805
    // https://crowcpp.org/master/guides/websockets/


    // Used to send clipboard data to the client
    // TODO: Improve, add authentication so this can't be spoofed
    // Full route path e.g. /api/clipboard/receive?username=sjobs1
    // Test using the cli: `curl "0.0.0.0:4800/api/clipboard/receive?username=<username>"`
    CROW_ROUTE(app, "/api/clipboard/receive") // URL query string: ?username=<username>
            .methods("GET"_method)
                    ([&userManager](const crow::request &req, crow::response &res) {
                        // Access query string parameters
                        auto username = req.url_params.get("username");
                        //auto deviceID = req.url_params.get("deviceID");

                        crow::json::wvalue jsonData;

                        // Set the content type response returned by the API
                        res.add_header("Content-Type", "application/json");

                        // Check if parameter(s) are present
                        if (username) {
                            try {
                                // Get latest clipboard entry
                                std::string userID = userManager.findUser(username);

                                if (userID.empty()) {
                                    res.code = 404; // Not Found
                                    jsonData["message"] = "No user match for the username";

                                    res.write(jsonData.dump());
                                } else {
                                    ClipboardEntry clipboardContents = *ClipboardHelper::getLatestClipboardEntry(userID);
                                    jsonData["content"] = clipboardContents.getContent();

                                    res.write(jsonData.dump());
                                }
                            } catch (const std::exception &e) {
                                res.code = 400; // Bad Request
                                jsonData["message"] = "Invalid username parameter";

                                res.write(jsonData.dump());
                            }
                        } else {
                            res.code = 400; // Bad Request
                            jsonData["message"] = "Missing username parameter";

                            res.write(jsonData.dump());
                        }

                        res.end();
                    });

    // Used login a user into the server
    CROW_ROUTE(app, "/api/auth/login")
            .methods("POST"_method)([&userManager](const crow::request &req) {
                std::cout << "Raw body: " << req.body << std::endl;

                auto jsonData = crow::json::load(req.body);

                if (!jsonData) {
                    crow::response res(400); // Set HTTP status code to 400 (Bad Request)
                    res.body = "Invalid JSON"; // Set response body to the error message
                    res.set_header("Content-Type", "text/plain");
                    return res;
                }


                if (userManager.authenticateUser(jsonData["username"].s(), jsonData["password"].s())) {
                    DeviceInfo *deviceInfo = userManager.finishUserLogIn(userManager.findUser(jsonData["username"].s()), "",
                                                jsonData["username"].s())->getDeviceInfo();

                    crow::response res(200);
                    res.body = deviceInfo->getDeviceId();
                    res.set_header("Content-Type", "text/plain");
                    return res;
                } else {
                    crow::response res(401);
                    res.body = "Authentication failed";
                    res.set_header("Content-Type", "text/plain");
                    return res;
                }
            });

    // Used register a user in the server
    CROW_ROUTE(app, "/api/auth/register")
            .methods("POST"_method)([&userManager](const crow::request &req) {
                std::cout << "Raw body: " << req.body << std::endl;

                auto jsonData = crow::json::load(req.body);

                if (!jsonData) {
                    crow::response res(400);
                    res.body = "Invalid JSON";
                    res.set_header("Content-Type", "text/plain");
                    return res;
                }


                std::string userID = userManager.registerUser(jsonData["username"].s(), jsonData["password"].s());
                if (userID.compare("") != 0) {
                    crow::response res(201); // 201 Created
                    res.body = "Registered! UserID: " + userID; // Optionally return the userID
                    return res;
                } else {
                    crow::response res(409); // 409 Conflict or 400 Bad Request
                    res.body = "Registration failed: Username might be already taken"; // Customize this message as needed
                    res.set_header("Content-Type", "text/plain");
                    return res;
                }
            });

    // Set the port, set app to run on multiple threads, and run the app synchronously
    app.port(PORT).multithreaded().run();
}