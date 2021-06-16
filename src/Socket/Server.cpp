//
// Created by isaac on 9/5/21.
//

#include "Server.h"
#include <zmq.hpp>
#include <iostream>


void Server::init() {

    // generate a request socket
    zmq::socket_type Type = type;
    socket= new zmq::socket_t(ctx, Type);

    // bind to the socket
    socket->bind(endpoint);
    std::cout<<"binded";
}

std::string Server::recieve() {
    zmq::message_t msg;
    socket->recv(msg);
    std::cout<<"[S]Recieved: "<<msg.to_string();
    return msg.to_string();
}

std::string Server::send(std::string msg) {
    zmq::message_t msg_send(msg);
    socket->send(msg_send, zmq::send_flags::none);
    std::cout<<"[S]Sended: "<<msg_send.to_string();
    return msg_send.to_string();
}

std::string Server::comunicatte(std::string msg) {
    return std::string();
}
