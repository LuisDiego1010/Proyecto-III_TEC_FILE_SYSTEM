//
// Created by isaac on 19/6/21.
//

#ifndef TEC_FILE_SYSTEM_NODECONTROLLER_H
#define TEC_FILE_SYSTEM_NODECONTROLLER_H
#include "Socket/Server.h"
#include "Socket/Client.h"


class NodeController {
    Server CESocket;
public:
/**
 * @brief Builder of the Node Controller
 * Establish port of the disk and create sockets
 */
    void create();
/**
 * @brief In charge of socket init for recive files
 */
    void Start();
/**
 * @brief In charge of the write of the file
 * Make the stripping and write in each disk the stripping
 */
    std::string Write(std::string&);
/**
 * @brief In charge of the Read of the file in the disknodes
 * if one disk fail recreate the data, takes 10 seg min to recreate the data
 */
    std::string Read(std::string&);
/**
 * @brief In charge of restore the data.
 * apply the XOR bit for each char of a string on a vector, work for create XOR and recreate the data
 */
    void XorBit(std::vector<std::string>&);

    std::vector<Socket_Client*> DISKS;
};


#endif //TEC_FILE_SYSTEM_NODECONTROLLER_H
