//
// Created by Jarrett Boersen on 2023-11-28.
//

#ifndef AIRCLIP_NETWORKCONNECTION_H
#define AIRCLIP_NETWORKCONNECTION_H

#include "crow.h"

class NetworkConnection {
private:
    static const unsigned short PORT;
public:
    static void startServer();
};


#endif //AIRCLIP_NETWORKCONNECTION_H
