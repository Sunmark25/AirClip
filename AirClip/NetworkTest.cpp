#include "crow.h"

int main() {
    crow::SimpleApp app; //define your crow application

    CROW_ROUTE(app, "/api/")([](){
        return "Hello world";
    });

    // TODO: Use to send data to the client
    // simple json response using a map
    // To see it in action enter {ip}:18080/api/send_json
    // it shoud show amessage before zmessage despite adding zmessage first.
    CROW_ROUTE(app, "/api/send_json")
            ([] {
                crow::json::wvalue x({{"zmessage", "Hello, World!"},
                                      {"amessage", "Hello, World2!"}});
                return x;
            });

    // To see it in action, I recommend to use the Postman Chrome extension:
    //      * Set the address to {ip}:18080/api/add_json
    //      * Set the method to post
    //      * Select 'raw' and then JSON
    //      * Add {"a": 1, "b": 1}
    //      * Send and you should receive 2

    // A simpler way for json example:
    //      * curl -d '{"a":1,"b":2}' {ip}:18080/api/add_json
    CROW_ROUTE(app, "/api/add_json")
            .methods("POST"_method)([](const crow::request& req) {
                auto x = crow::json::load(req.body);
                if (!x)
                    return crow::response(400);
                int sum = x["a"].i() + x["b"].i();
                std::ostringstream os;
                os << sum;
                return crow::response{os.str()};
            });

    // TODO: Use to receive data from the client
    // TODO: Improve, add authentication so this can't be spoofed
    // Use: `curl -d '{"username":"<username>","content":"<string-content>"}' 0.0.0.0:18080/api/clipboard/send`
    CROW_ROUTE(app, "/api/clipboard/send")
            .methods("POST"_method)([](const crow::request& req) {
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

    //set the port, set the app to run on multiple threads, and run the app
    app.port(49162).multithreaded().run(); // .bindaddr("10.0.0.34")
}