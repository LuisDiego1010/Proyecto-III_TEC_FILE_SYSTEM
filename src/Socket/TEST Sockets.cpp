//
// Created by isaac on 15/6/21.
//
#include <iostream>
#include "Huffman.h"
int main(){
    auto msg=std::string("Pablito clavo un clavito, un clavito clavo pablito, que clavo pablito?");

    auto a= Encode(msg);
    std::cout<<std::endl;
    auto b= Encode(a,2);
}
