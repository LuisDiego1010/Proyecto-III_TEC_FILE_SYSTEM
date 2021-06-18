//
// Created by isaac on 15/6/21.
//

#ifndef TEC_FILE_SYSTEM_HUFFMAN_H
#define TEC_FILE_SYSTEM_HUFFMAN_H

#include <string>
#include <vector>

struct Node{
public:
    bool operator>(Node other) const{
        return this->quantity>other.quantity;
    };
    bool operator<(Node other) const{
        return this->quantity<other.quantity;
    };
    bool operator==(int other) const{
        return this->quantity==other;
    };
    bool operator!=(int other) const{
        return this->quantity!=other;
    };
    Node();
    long quantity=0;
    std::string character;
    std::string code;
};

struct TreeNode:Node{
    TreeNode(TreeNode* left,TreeNode* rigth);
    TreeNode();
    bool isLeaf() const{
        return left == rigth;
    };
    TreeNode* left= nullptr;
    TreeNode* rigth= nullptr;
};

void SortVec(std::vector<TreeNode>&, long );
void InsertNode(std::vector<TreeNode>&, TreeNode, long);
std::string Encode(const std::string&);
void CreateList(std::vector<TreeNode>&,const std::string&);
TreeNode* CreateTree(std::vector<TreeNode>&);
void CreateTable(std::vector<Node>&, TreeNode*, const std::string&);

#endif //TEC_FILE_SYSTEM_HUFFMAN_H