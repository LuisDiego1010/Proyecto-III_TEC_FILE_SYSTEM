//
// Created by isaac on 19/6/21.
//

#ifndef TEC_FILE_SYSTEM_NODECONTROLLER_H
#define TEC_FILE_SYSTEM_NODECONTROLLER_H
#include "Socket/Server.h"
#include "Socket/Client.h"


class NodeController {
    Server CESocket;
    std::vector<Socket_Client*> DISKS;
public:
    void create();
};


#endif //TEC_FILE_SYSTEM_NODECONTROLLER_H
