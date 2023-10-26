//
// Created by Tingrui Zhang on 2023-10-25.
//

#ifndef AIRCLIP_AIRCLIPSERVER_H
#define AIRCLIP_AIRCLIPSERVER_H
//#include "UserManager.h"
#include "NetworkConnection.h"

class AirClipServer{
private:
    //UserManager userManager();

    void stopServer();
    void newConnection(std::string wtConnectionId);

public:
    void startServer();
};

#endif //AIRCLIP_AIRCLIPSERVER_H
