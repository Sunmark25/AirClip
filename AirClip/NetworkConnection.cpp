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
#include "UserManager.h"
#include "ClipboardHelper.h"

const unsigned short NetworkConnection::PORT = 48000;

void NetworkConnection::startServer() {
    std::cout << "Starting HTTP API" << std::endl;

    crow::SimpleApp app; // Define the crow application
    UserManager userManager = UserManager();

    CROW_ROUTE(app, "/api/")([]() {
        return "Welcome to the API";
    });

    // Used to receive clipboard data from the client
    // TODO: Improve, add authentication so this can't be spoofed
    // Use: `curl -d '{"username":"<username>","content":"<string-content>"}' 0.0.0.0:18080/api/clipboard/send`
    CROW_ROUTE(app, "/api/clipboard/send")
            .methods("POST"_method)([](const crow::request &req) {
                std::cout << "Raw body: " << req.body << std::endl;

                auto jsonData = crow::json::load(req.body);

                if (!jsonData)
                    return crow::response(400);

                // TODO: Put in Database
                std::cout << "Username: " << jsonData["username"].s() << std::endl;
                std::cout << "Content: " << jsonData["content"].s() << std::endl;


                return crow::response{"Received!"};
            });

    // TODO: Implement a websocket to listen for clipboard changes from the server
    // https://stackoverflow.com/a/12442805
    // https://crowcpp.org/master/guides/websockets/


    // Used to send clipboard data to the client
    // TODO: Improve, add authentication so this can't be spoofed
    // Full route path e.g. /api/clipboard/receive?username=sjobs1
    CROW_ROUTE(app, "/api/clipboard/receive") // URL query string: ?username=<user's username>
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
                                    jsonData["contents"] = clipboardContents.getContent();

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

                if (!jsonData)
                    return crow::response(400);


                // TODO: Login user
                if (userManager.authenticateUser(jsonData["username"].s(), jsonData["password"].s())) {
                    userManager.finishUserLogIn(userManager.findUser(jsonData["username"].s()), "",
                                                jsonData["username"].s());
                    return crow::response{"Logged in!"}; // TODO: Change to something better? UserID? WtConnectionID?
                    //TODO: return Login Info Over Here
                }


                return crow::response{"Logged in!"}; // TODO: Change to something better? UserID? WtConnectionID?
            });

    // Used register a user in the server
    CROW_ROUTE(app, "/api/auth/register")
            .methods("POST"_method)([&userManager](const crow::request &req) {
                std::cout << "Raw body: " << req.body << std::endl;

                auto jsonData = crow::json::load(req.body);

                if (!jsonData)
                    return crow::response(400);


                std::string userID = userManager.registerUser(jsonData["username"].s(), jsonData["password"].s());
                if (userID.compare("") != 0) {
                    return crow::response{"Registered!"};
                } else {
                    // TODO: Implement Not Registered Logic Here
                }


                return crow::response{"Registered!"}; // TODO: Change to something better? UserID? WtConnectionID?
            });

    // Set the port, set app to run on multiple threads, and run the app synchronously
    app.port(PORT).multithreaded().run();
}