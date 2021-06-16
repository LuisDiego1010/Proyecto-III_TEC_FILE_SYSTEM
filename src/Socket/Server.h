/**
  * @file Server.h
  * */


#ifndef PROYECTO_II_SOCKET_SERVER_H
#define PROYECTO_II_SOCKET_SERVER_H
#include <zmq.hpp>

#define port "4040"
#define type zmq::socket_type::req

class Server {
public:
    static Server* self;

    zmq::context_t ctx;
    std::string endpoint="tcp://*:";

    zmq::socket_t * socket;

    /**
     * \brief Call at the start of the Server, No need to be called again.
     * Init and connect the socket
     */
    void init();
    /**
     * \brief Virtual 1-1 conection
     * @return
     */
    virtual std::string comunicatte(std::string);
    /**
     * Wait for a msg from the client
     * @return the msg of the cleint as String
     */
    std::string recieve();

    /**
     * send a msg to the client
     * @return the same msg
     */
    std::string send(std::string);

    std::string HuffmanEncode(std::string);
    std::string HuffmanDecode(std::string);

};


#endif //PROYECTO_II_SOCKET_SERVER_H
