//
// Created by isaac on 15/6/21.
//

#include "Huffman.h"
#include <utility>
#include <vector>
#include <iostream>
#include <nlohmann/json.hpp>

Node::Node() {
    quantity = 0;
}

void SortVec(std::vector<TreeNode> &vector, long position = 0) {
    for (long k = position; k + 1 < vector.size(); ++k) {
        if ((vector[k] > vector[k + 1]) && vector[k + 1] != 0) {
            auto tmpN = vector[k];
            vector[k] = vector[k + 1];
            vector[k + 1] = tmpN;
        } else {
            break;
        }
    }
}

void InsertNode(std::vector<TreeNode> &vector, TreeNode node, long position = 0) {
    for (unsigned long i = vector.size() - 1; i > position; --i) {
        vector[i] = vector[i - 1];
    }
    vector[position] = std::move(node);
    SortVec(vector, position);
}

void CreateList(std::vector<TreeNode> &Nodes, const std::string &msg) {
    for (int i = 0; i < msg.size(); i += Dividition) {
        for (int j = 0; j < Nodes.size() + 1; ++j) {
            if (j + 1 > Nodes.size()) {
                auto tmp = TreeNode();
                tmp.character = msg.substr(i, Dividition);
                tmp.quantity = 1;
                Nodes.insert(Nodes.begin(), tmp);
                break;
            } else {
                if (Nodes[j].character == msg.substr(i, Dividition)) {
                    Nodes[j].quantity++;
                    if (j + 1 == Nodes.size()) {
                        break;
                    }
                    SortVec(Nodes, j);
                    break;
                } else {
                    continue;
                }
            }
        }
    }
}

TreeNode *CreateTree(std::vector<TreeNode> &SortedList) {
    u_long lopp = SortedList.size();
    SortedList.resize(lopp * 2 - 1);
    long pos = 0;
    while (lopp > 1) {
        auto tmp = TreeNode(&SortedList[pos], &SortedList[pos + 1]);
        pos += 2;
        InsertNode(SortedList, tmp, pos);
        lopp--;
    }
    return &SortedList[SortedList.size() - 1];
}

void CreateTable(std::map<std::string, std::string> &Table, TreeNode *node, const std::string &msg = "") {
    if (node->isLeaf()) {
        Table[node->character] = msg;
        return;
    }
    if (node->left != nullptr) {
        CreateTable(Table, node->left, msg + "0");
    }
    if (node->rigth != nullptr) {
        CreateTable(Table, node->rigth, msg + "1");
    }
}

std::string Encode(const std::string &msg, int dividition) {
    Dividition = dividition;
//    Get characters and sort it
    std::vector<TreeNode> Nodes;
    CreateList(Nodes, msg);

// list copy to send and sort the original list to coincide to the copy
    std::map<std::string, long> Dict;
    for (const TreeNode &a:Nodes) {
        Dict[a.character] = a.quantity;
    }
    Nodes.clear();

    for (const auto&[key, value]:Dict) {
        TreeNode temp=TreeNode();
        temp.character=key;
        temp.quantity=value;
        Nodes.insert(Nodes.begin(), temp);
        SortVec(Nodes);
    }

//Create Tree
    TreeNode *tree = CreateTree(Nodes);
//    Create table from the tree root node
    std::map<std::string, std::string> Table;
    CreateTable(Table, tree);

//Encode using the table
    std::string d;
    for (int i = 0; i < msg.size(); i += Dividition) {
        d += Table[msg.substr(i, Dividition)];
    }
//    Create the json
    nlohmann::basic_json<> data;
    data["data"] = d;
    data["dict"] = Dict;

    return to_string(data);
}

std::string Decode(const std::string* msg){
    nlohmann::basic_json<> data=nlohmann::basic_json<>::parse(*msg);
//    Get the dict of the word
    std::map<std::string, long> Dict=data["dict"];
//    Recreeate from the dict the treenode vector.
    std::vector<TreeNode> Nodes;
    for (const auto&[key, value]:Dict) {
        TreeNode temp=TreeNode();
        temp.character=key;
        temp.quantity=value;
        Nodes.insert(Nodes.begin(), temp);
        SortVec(Nodes);
    }

//Create the Tree
    TreeNode *tree = CreateTree(Nodes);
    std::map<std::string, std::string> Table;
    CreateTable(Table, tree);

// run the tree with the msg
    std::string decoded;
    std::string EncodedMsg=data["data"];
    RunTree(tree, EncodedMsg, decoded, nullptr);

//    std::cout << to_string(data);
    return decoded;


}
void RunTree(TreeNode* node,std::string& msg,std::string& Decoded, long* position= nullptr){
    if(position== nullptr){
        long a=0;
        position=&a;
        while(*position<=msg.size()-1
        ){
            RunTree(node,msg, Decoded, position);
        }
        return;
    }

    if(node->isLeaf()){
        Decoded+=node->character;
        return;
    }

    if((msg.substr((*position),1)) == std::string("1")){
        (*position)++;
        RunTree(node->rigth,msg, Decoded, position);
    }else{
        (*position)++;
        RunTree(node->left,msg, Decoded, position);
    }


}


TreeNode::TreeNode(TreeNode *left, TreeNode *rigth) {
    this->rigth = rigth;
    this->left = left;
    this->quantity += left->quantity;
    this->quantity += rigth->quantity;
}

TreeNode::TreeNode() = default;
