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
#include "UserManager.h"

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
    std::string deleteAllUser = "DROP TABLE User;";
    std::string deleteAllDevice = "DROP TABLE Device;";
    std::string deleteAllClipboardEntry = "DROP TABLE ClipboardEntry;";
    DatabaseController *dbc = DatabaseController::getInstance();

    dbc->sqlOperation(deleteAllUser);
    dbc->sqlOperation(deleteAllDevice);
    dbc->sqlOperation(deleteAllClipboardEntry);
    dbc->createTable();


    UserManager userManager = UserManager();
    std::string benzUserID = userManager.registerUser("Benz", "helloWorld");

    if (userManager.authenticateUser("Benz","helloWorld")){
        std::cout << "Hello World" << std::endl;
    }

    Device *device = userManager.finishUserLogIn(benzUserID, "56", "Benz");
    std::string benzMacbookDeviceID = device->registerDevice("Benz Macbook Air", benzUserID);
    Device *device1 = userManager.finishUserLogIn(benzUserID, "58", "Benz");
    std::string benzIPadDeviceID = device1->registerDevice("Benz ipad", benzUserID);

    std::string query = ClipboardHelper::generateClipboardEntryInsertSQL(ClipboardHelper::generateCurrentTime(), benzMacbookDeviceID, "Hello World From Mac", "", "");
    dbc->sqlOperation(query);
    std::string ceid1 = ClipboardHelper::insertClipboardEntry(ClipboardHelper::generateCurrentTime(), benzMacbookDeviceID, "Hello World From Mac", "", "");
    std::string ceid2 = ClipboardHelper::insertClipboardEntry(ClipboardHelper::generateCurrentTime(), benzIPadDeviceID, "Hello World From iPad");
    std::string ceid3 = ClipboardHelper::insertClipboardEntry(ClipboardHelper::generateCurrentTime(), benzMacbookDeviceID, "This is a test message from Mac");
    std::string ceid4 = ClipboardHelper::insertClipboardEntry(ClipboardHelper::generateCurrentTime(), benzIPadDeviceID, "This is a test message from iPad");


    std::vector test = ClipboardHelper::searchClipboardEntry("Hello");
    for (int i = 0; i < test.size(); ++i) {
        std::cout << test[i]->getContent() << std::endl;
    }
    std::cout << std::endl << "Latest User Content: " << ClipboardHelper::getLatestClipboardEntry()->getContent();
    std::cout << std::endl << "Latest Device Content: " << ClipboardHelper::getLatestClipboardEntry(benzIPadDeviceID)->getContent() << std::endl;

    std::vector test1 = ClipboardHelper::getClipboardEntries(benzUserID);
    for (int i = 0; i < test.size(); ++i) {
        std::cout << test1[i]->getContent() << std::endl;
    }



    try {
        Wt::WServer server;

        // If there is one then use the hardcoded arguments
        if (argc == 1) {
            // Get the executable name from the first argument (always set)
            std::string executableName = argv[0];

            // Used to store the hardcode the command-line arguments
            const std::vector<std::string> hardcodedArgs = {"--docroot", ".", "--http-listen", "0.0.0.0:8080"};

            server.setServerConfiguration(executableName, hardcodedArgs, WTHTTP_CONFIGURATION);
        } else { // Otherwise, use the command-line arguments
            server.setServerConfiguration(argc, argv, WTHTTP_CONFIGURATION);
        }

        // need to define device before it is being used!!!
        server.addEntryPoint(Wt::EntryPointType::Application,
                             [&device](const Wt::WEnvironment &env) {
                                 static int deviceCounter = 0;

                                 return device->associateWithSession(env);
                             }
        );

        // Start server
        if (server.start()) {
            Wt::WServer::waitForShutdown();

            std::cerr << "Shutdown" << std::endl;
            server.stop();

            // Restart logic, if necessary, should be handled here
        }
    } catch (Wt::WServer::Exception &e) {
        std::cerr << e.what() << std::endl;
    } catch (std::exception &e) {
        std::cerr << "exception: " << e.what() << std::endl;
    }

    return 0;
}

