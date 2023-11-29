//
// Created by Jarrett Boersen on 2023-11-28.
//

#ifndef AIRCLIP_NETWORKCONNECTION_H
#define AIRCLIP_NETWORKCONNECTION_H

#include "crow.h"

class NetworkConnection {
private:
    const unsigned short *PORT = reinterpret_cast<const unsigned short *>(48000);
public:
    void startServer();
};


#endif //AIRCLIP_NETWORKCONNECTION_H
