//
// Created by isaac on 15/6/21.
//

#ifndef TEC_FILE_SYSTEM_HUFFMAN_H
#define TEC_FILE_SYSTEM_HUFFMAN_H

#include <string>

struct Node{
    bool operator>(Node other){
        return this->quantity>other.quantity;
    };
    Node();
    int quantity=0;
    char character{};
};
struct TreeNode{
    Node *value;
    TreeNode* left;
    TreeNode* Rigth;
};
std::string Encode(const std::string&);

#endif //TEC_FILE_SYSTEM_HUFFMAN_H
