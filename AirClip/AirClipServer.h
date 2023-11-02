//
// Created by Tingrui Zhang on 2023-10-25.
//

#ifndef AIRCLIP_AIRCLIPSERVER_H
#define AIRCLIP_AIRCLIPSERVER_H
#include "UserManager.h"

class AirClipServer{
private:
    UserManager userManager();
    int main();
    void startServer();
    void stopServer();
    void newConnection(std::string wtConnectionId);
};

#endif //AIRCLIP_AIRCLIPSERVER_H
