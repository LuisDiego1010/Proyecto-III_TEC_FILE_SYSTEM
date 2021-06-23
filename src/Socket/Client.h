//
// Created by isaac on 19/6/21.
//

#ifndef TEC_FILE_SYSTEM_CLIENT_H
#define TEC_FILE_SYSTEM_CLIENT_H
#include <zmq.hpp>
#include "Huffman.h"

class Socket_Client {
public:


    zmq::context_t ctx;
    std::string endpoint="tcp://127.0.0.1:";
    std::string port="4040";
    zmq::socket_t * socket;

    /**
     * \brief send a String to server and return the server answer.
     * @return
     */
    std::string comunicatte(std::string);

    /**
     * \brief In charge of set the client port
     */
    void setPort(const std::string &port);

    /**
     * \brief Initializer of the socket, create the singleton and connect to the server
     */

    void Init();


};



#endif //TEC_FILE_SYSTEM_CLIENT_H
