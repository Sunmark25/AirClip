//
// Created by Tingrui Zhang on 2023-10-25.
//

#ifndef AIRCLIP_AIRCLIPSERVER_H
#define AIRCLIP_AIRCLIPSERVER_H
#include "UserManager.h"
#include "NetworkConnection.h"

class AirClipServer{
private:
    UserManager *userManager;

    void stopServer();

    /**
     * This method is used to handle a new connection to the server
     *
     * @param wtConnectionId The wt connection ID which corresponds to the user
     */
    void newConnection(const std::string &wtConnectionId);

public:
    explicit AirClipServer() {
        userManager = new UserManager();
    }

    void startServer();
};

#endif //AIRCLIP_AIRCLIPSERVER_H
