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
    void Start();
    std::string Write(std::string&);
    std::string Read(std::string&);
    std::string Dir();
    void XorBit(std::vector<std::string>&);
};


#endif //TEC_FILE_SYSTEM_NODECONTROLLER_H
