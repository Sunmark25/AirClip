/**
 * @class NetworkConnection
 * @brief Manages network connections for a server-client architecture.
 *
 * This class handles network-related functionalities such as starting a server,
 * accepting client connections, and performing data read and write operations over the network.
 * It uses socket programming to establish and manage TCP connections.
 */

#include "NetworkConnection.h"

void NetworkConnection::startServer() {
    crow::SimpleApp app; // Define the crow application

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

                std::cout << "Username: " << jsonData["username"].s() << std::endl;
                std::cout << "Content: " << jsonData["content"].s() << std::endl;

                return crow::response{"Received!"};
            });

    // TODO: Implement a websocket to listen for clipboard changes from the server
    // https://stackoverflow.com/a/12442805
    // https://crowcpp.org/master/guides/websockets/

    std::string clipboardContent = "Test data 123";

    // Used to send clipboard data to the client
    // TODO: Improve, add authentication so this can't be spoofed
    CROW_ROUTE(app, "/api/clipboard/receive")
            .methods("GET"_method)([&clipboardContent] {
                crow::json::wvalue x({"content", clipboardContent});
                return x;
            });

    // Used login a user into the server
    CROW_ROUTE(app, "/api/auth/login")
            .methods("POST"_method)([](const crow::request &req) {
                std::cout << "Raw body: " << req.body << std::endl;

                auto jsonData = crow::json::load(req.body);

                if (!jsonData)
                    return crow::response(400);

                std::cout << "Username: " << jsonData["username"].s() << std::endl;
                std::cout << "Password: " << jsonData["password"].s() << std::endl;

                // TODO: Login user

                return crow::response{"Logged in!"}; // TODO: Change to something better? UserID? WtConnectionID?
            });

    // Used register a user in the server
    CROW_ROUTE(app, "/api/auth/register")
            .methods("POST"_method)([](const crow::request &req) {
                std::cout << "Raw body: " << req.body << std::endl;

                auto jsonData = crow::json::load(req.body);

                if (!jsonData)
                    return crow::response(400);

                std::cout << "Username: " << jsonData["username"].s() << std::endl;
                std::cout << "Password: " << jsonData["password"].s() << std::endl;

                // TODO: Register user

                return crow::response{"Registered!"}; // TODO: Change to something better? UserID? WtConnectionID?
            });

    // Set the port, set app to run on multiple threads, and run the app
    app.port(49162).multithreaded().run(); // .bindaddr("10.0.0.34")
}