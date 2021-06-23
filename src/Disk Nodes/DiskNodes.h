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
    int elements=0;
    int parity=0;
    void create();

    int Write(std::string &, bool= true);

    std::string Read(std::string &);

    static void Start();

    /**
     * Get the number of blocks
     */
    void count_dir();

    std::string list_dir();
    static int filter(const struct dirent*);
};

#endif //TEC_FILE_SYSTEM_DISKNODES_H
