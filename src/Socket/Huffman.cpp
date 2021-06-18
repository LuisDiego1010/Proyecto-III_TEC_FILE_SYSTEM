//
// Created by isaac on 15/6/21.
//

#include "Huffman.h"
#include <utility>
#include <vector>
#include <iostream>
#define dividition 1
Node::Node() {
    quantity = 0;
}

void SortVec(std::vector<TreeNode> &vector, long position = 0) {
    for (long k = position; k + 1 < vector.size(); ++k) {
        if (vector[k] > vector[k + 1]&&vector[k + 1]!=0) {
            auto tmpN = vector[k];
            vector[k] = vector[k + 1];
            vector[k + 1] = tmpN;
        } else {
            break;
        }
    }
}
void InsertNode(std::vector<TreeNode> &vector, TreeNode node, long position= 0){
    for (unsigned long i = vector.size()-1; i > position; --i) {
        vector[i]=vector[i-1];
    }
    vector[position]=std::move(node);
    SortVec(vector,position);
}
void CreateList(std::vector<TreeNode>& Nodes, const std::string& msg) {
    for (int i=0; i<msg.size();i+=dividition) {
        for (int j = 0; j < Nodes.size() + 1; ++j) {
            if (j + 1 > Nodes.size()) {
                auto tmp = TreeNode();
                tmp.character = msg.substr(i,dividition);
                tmp.quantity = 1;
                Nodes.insert(Nodes.begin(), tmp);
                break;
            } else {
                if (Nodes[j].character == msg.substr(i,dividition)) {
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
TreeNode* CreateTree(std::vector<TreeNode>& SortedList){
    u_long lopp=SortedList.size();
    SortedList.resize(lopp*2-1);
    long pos=0;
    while(lopp>1){
        auto tmp = TreeNode(&SortedList[pos],&SortedList[pos+1]);
        pos+=2;
        InsertNode(SortedList,tmp,pos);
        lopp--;
    }
    return &SortedList[SortedList.size()-1];
}
void CreateTable(std::vector<Node>& Table, TreeNode* node, const std::string& msg=""){
    if(node->isLeaf()){
        Node tmp= (Node)*node;
        tmp.code=msg;
        Table.push_back(tmp);
        return;
    }
    if(node->left!= nullptr){
        CreateTable(Table, node->left, msg+"0");
    }
    if(node->rigth != nullptr){
        CreateTable(Table, node->rigth, msg+"1");
    }
}
std::string Encode(const std::string &msg) {
    std::vector<TreeNode> Nodes;
    CreateList(Nodes, msg);
    TreeNode* tree=CreateTree(Nodes);
    std::vector<Node> Table;
    CreateTable(Table, tree);
    std::cout << "Nodes";
    for (const Node& a:Nodes) {
        std::cout << a.quantity;
        std::cout << a.character;
        std::cout << std::endl;
    }
    std::cout << std::endl;
    std::cout << "Table"<<std::endl;
    for (const Node& a:Table) {
        std::cout << a.character << "|"<< a.code;
        std::cout << std::endl;
    }
    std::string d;
    for (int i=0; i<msg.size();i+=dividition) {
        for(const Node& b:Table){
            if(msg.substr(i,dividition)==b.character){
                d+=b.code;
                break;
            }
        }
    }
    std::cout<<d;
    return d;
}
TreeNode::TreeNode(TreeNode *left, TreeNode *rigth) {
    this->rigth = rigth;
    this->left = left;
    this->quantity += left->quantity;
    this->quantity += rigth->quantity;
}
TreeNode::TreeNode() = default;
