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
/**
 * @brief
 */
    void create();
/**
 * @brief In charge of socket init for recive files
 */
    void Start();
/**
 * @brief In charge of the write of the file
 */
    std::string Write(std::string&);
/**
 * @brief In charge of the Read of the file
 */
    std::string Read(std::string&);
/**
 * @brief In charge of restore the data
 */
    std::string Dir();


    void XorBit(std::vector<std::string>&);
};


#endif //TEC_FILE_SYSTEM_NODECONTROLLER_H
