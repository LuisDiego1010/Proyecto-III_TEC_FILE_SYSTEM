//
// Created by isaac on 15/6/21.
//
#include <iostream>
#include "Huffman.h"
#include "Client.h"
#include "Server.h"
int main(){
    auto msg=std::string("En algun lugar de la mancha cuyo nombre no puedo recordar, Se encontraba Don Quijote, o algo asi, no recuerdo como empezaba el libro ya");
    std::string a;
    a= Huffman::Encode(msg);
    std::cout<<std::endl;
    std::string b= Huffman::Decode(&a);
    std::cout<<std::endl;
    std::cout<<b;


    Socket_Client client=Socket_Client();
    Server server;
    client.setPort("4043");
    server.setPort("4040");
    client.Init();
    std::cout<<std::endl;
    std::cout<<client.comunicatte("stop");


    exit(0);

}
