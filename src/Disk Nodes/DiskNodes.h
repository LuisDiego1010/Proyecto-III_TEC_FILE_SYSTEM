//
// Created by isaac on 19/6/21.
//

#ifndef TEC_FILE_SYSTEM_DISKNODES_H
#define TEC_FILE_SYSTEM_DISKNODES_H
#include "Socket/Server.h"
int DiskSize {150};
int BlockSize {2048};
class DiskNodes {
public:
    Server Socket;
    std::string dir;
    void create();
    void Write(std::string&);
    static void Start();
};

#endif //TEC_FILE_SYSTEM_DISKNODES_H
