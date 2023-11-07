//
// Created by Tingrui Zhang on 2023-10-25.
//

#ifndef AIRCLIP_AIRCLIPSERVER_H
#define AIRCLIP_AIRCLIPSERVER_H

#include <iostream>
#include "DatabaseController.h"
#include "UserManager.h"
#include "NetworkConnection.h"

class AirClipServer {
private:
    const char *DB_PATH = "../../AirClip.sqlite"; // TODO: Move?
    UserManager *userManager;

    void stopServer();

    /**
     * This method is used to handle a new connection to the server
     *
     * @param wtConnectionId The wt connection ID which corresponds to the user
     */
    void newConnection(const std::string &wtConnectionId);

public:
    AirClipServer() {
        // Start the database controller and pass in the db filepath
        DatabaseController::getInstance(DB_PATH);

        // Create a new UserManager and store it in the point
        userManager = new UserManager();
    }

    void startServer();
};

#endif //AIRCLIP_AIRCLIPSERVER_H
