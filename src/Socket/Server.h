/**
  * @file Server.h
  * */


#ifndef PROYECTO_II_SOCKET_SERVER_H
#define PROYECTO_II_SOCKET_SERVER_H
#include <zmq.hpp>
#include "Huffman.h"

#define type zmq::socket_type::req

class Server {
public:
    Server* self;

    zmq::context_t ctx;
    std::string endpoint="tcp://*:";
    std::string Port="4040";

    zmq::socket_t * socket;

    /**
     * \brief Call at the start of the Server, No need to be called again.
     * Init and connect the socket
     */
    void init();

    /**
     * Wait for a msg from the client
     * @return the msg of the client as String
     */
    std::string recieve();

    /**
     * send a msg to the client
     * @return the same msg
     */
    std::string send(std::string);

};


#endif //PROYECTO_II_SOCKET_SERVER_H
