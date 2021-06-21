//
// Created by isaac on 9/5/21.
//

#include "Server.h"
#include <zmq.hpp>
#include <iostream>


void Server::Init() {

    // generate a request socket
    zmq::socket_type Type = type;
    socket= new zmq::socket_t(ctx, Type);
    self= this;
    // bind to the socket
    endpoint=endpoint+Port;
    socket->bind(endpoint);
    std::cout<<"binded";
}

std::string Server::recieve() {
//    Recieve
    zmq::message_t msg;
    socket->recv(msg);
    std::cout<<"[S]Recieved: "<<msg.to_string();
//   Decode
    std::string recieved=msg.to_string();
    recieved= Huffman::Decode(&recieved);
    return recieved;
}

std::string Server::send(std::string msg) {
//    Encode
    msg= Huffman::Encode(msg);
//    Send
    zmq::message_t msg_send(msg);
    socket->send(msg_send, zmq::send_flags::none);
    std::cout<<"[S]Sended: "<<msg_send.to_string();
    return msg_send.to_string();
}

void Server::setPort(const std::string &port) {
    Port = port;
}

