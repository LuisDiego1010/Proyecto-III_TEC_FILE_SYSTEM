//
// Created by isaac on 19/6/21.
//

#ifndef TEC_FILE_SYSTEM_DISKNODES_H
#define TEC_FILE_SYSTEM_DISKNODES_H
#include "Socket/Server.h"

class DiskNodes {
public:
    Server Socket;
    FILE* Fdata;
    std::string dir;
    void create();
};


#endif //TEC_FILE_SYSTEM_DISKNODES_H
