//
// Created by isaac on 19/6/21.
//

#include <iostream>
#include "Client.h"
void Socket_Client::Init() {
    // generate a request socket
    zmq::socket_type type = zmq::socket_type::req;
    socket= new zmq::socket_t(ctx, type);
    endpoint=endpoint+port;
    socket->connect(endpoint);
}

std::string Socket_Client::comunicatte(std::string msg, int time) {
//    Code
    msg=Huffman::Encode(msg);
    int flag=1;
//    Send
    if(time>0){
        zmq::pollitem_t iteration={(void*)*socket,0,ZMQ_POLLOUT,0};
        flag= zmq_poll(&iteration,1,time);
        if(flag<=0){
            std::cout<<zmq_strerror(zmq_errno());
            return"error1";
        }
    }
    zmq::message_t msg_send(msg);


    socket->send(msg_send,zmq::send_flags::none);
    std::cout<<"[C]Sended: "<<msg_send;
    //    Recieve
    if(time>1){

        zmq::pollitem_t iteration={(void*)*socket,0,ZMQ_POLLIN,0};
        flag= zmq_poll(&iteration,1,time);
        if(flag<0){
            std::cout<<zmq_strerror(errno);
            return"error2";
        }

    }
    zmq::message_t msg_recieve;
    socket->recv(msg_recieve);
    std::cout<<"[C]Recieved: "<<msg_recieve;

//    Decode
    msg=msg_recieve.to_string();
    msg= Huffman::Decode(&msg);

    return msg;
}

void Socket_Client::setPort(const std::string &port) {
    Socket_Client::port = port;
}
