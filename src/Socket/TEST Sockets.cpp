//
// Created by isaac on 15/6/21.
//
#include <iostream>
#include "Huffman.h"
int main(){
    auto msg=std::string("En algun lugar de la mancha cuyo nombre no puedo recordar, Se encontraba Don Quijote, o algo asi, no recuerdo como empezaba el libro ya");
    std::string a;
    a= Huffman::Encode(msg);
    std::cout<<std::endl;
    std::string b= Huffman::Decode(&a);
    std::cout<<std::endl;
    std::cout<<b;


    auto first=


}
