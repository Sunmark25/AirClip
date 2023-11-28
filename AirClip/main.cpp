/**
 * @file main.cpp
 * @brief Main entry point for the AirClip application.
 *
 * This file contains the main function and the application factory function for the AirClip application.
 * It uses the Wt library to create a web application.
 */

#include <Wt/WApplication.h>
#include <Wt/WServer.h>
#include "UI.h"
#include "Device.h"

/**
 * @brief Creates and configures the AirClip application.
 *
 * This factory function creates a new instance of Wt::WApplication configured for the AirClip application.
 * It sets the title of the application and adds the main UI to the root container of the application.
 *
 * @param env The environment configuration provided by Wt.
 * @return std::unique_ptr<Wt::WApplication> A unique pointer to the created Wt::WApplication instance.
 */
//std::unique_ptr<Wt::WApplication> AirClipApplication(const Wt::WEnvironment& env) {
//    auto app = std::make_unique<Wt::WApplication>(env);
//    app->setTitle("AirClip");  // Set the title
//    // Add your UI to the root container of the application.
//    app->root()->addWidget(std::make_unique<UI>());
//    return app;
//}

int main(int argc, char **argv) {
    try {
        Wt::WServer server;

        // Check command-line arguments
        if (argc == 1) {
            char* args[] = {"--docroot", ".", "--http-listen", "0.0.0.0:8080"};
            int argCount = sizeof(args) / sizeof(char*);
            server.setServerConfiguration(argCount, args, WTHTTP_CONFIGURATION);
        } else {
            server.setServerConfiguration(argc, argv, WTHTTP_CONFIGURATION);
        }

        server.addEntryPoint(Wt::EntryPointType::Application,
                             [](const Wt::WEnvironment& env) {
                                 std::string deviceID = "device123";  // Example device ID
                                 std::string userID = "user456";      // Example user ID

                                 Device device(deviceID);
                                 return device.associateWithSession(env);
                             }
        );

        // Start server
        if (server.start()) {
            Wt::WServer::waitForShutdown();

            std::cerr << "Shutdown" << std::endl;
            server.stop();

            // Restart logic, if necessary, should be handled here
        }
    } catch (Wt::WServer::Exception& e) {
        std::cerr << e.what() << std::endl;
    } catch (std::exception& e) {
        std::cerr << "exception: " << e.what() << std::endl;
    }

    return 0;
}

