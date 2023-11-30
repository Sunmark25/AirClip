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

//    std::string clipboardContent = "Test data 123";

    // Used to send clipboard data to the client
    // TODO: Improve, add authentication so this can't be spoofed
    CROW_ROUTE(app, "/api/clipboard/receive")
            .methods("GET"_method)([&userManager] {
                // Create a crow::json::wvalue object
                crow::json::wvalue responseJson;


                // TODO: Put in Database
                // Add a key-value pair to the JSON object
//                responseJson["content"] = clipboardContent;

//                std::string userID = userManager.findUser(jsonData["username"].s());
//                ClipboardHelper::getClipboardEntries(userID);

                // Return the JSON object as the response
                return responseJson;
            });

    // Used login a user into the server
    CROW_ROUTE(app, "/api/auth/login")
            .methods("POST"_method)([&userManager](const crow::request &req) {
                std::cout << "Raw body: " << req.body << std::endl;

                auto jsonData = crow::json::load(req.body);

                if (!jsonData)
                    return crow::response(400);


                // TODO: Login user
                if (userManager.authenticateUser( jsonData["username"].s(),jsonData["password"].s())){
                    userManager.finishUserLogIn(userManager.findUser(jsonData["username"].s()), "", jsonData["username"].s());
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
                if (userID.compare("") != 0){
                    return crow::response{"Registered!"};
                } else {
                    // TODO: Implement Not Registered Logic Here
                }


                return crow::response{"Registered!"}; // TODO: Change to something better? UserID? WtConnectionID?
            });

    // Set the port, set app to run on multiple threads, and run the app synchronously
    app.port(PORT).multithreaded().run();
}