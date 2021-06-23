//
// Created by isaac on 15/6/21.
//

#ifndef TEC_FILE_SYSTEM_HUFFMAN_H
#define TEC_FILE_SYSTEM_HUFFMAN_H

#include <string>
#include <vector>
#include <map>
namespace Huffman{
        struct Node;
        struct TreeNode;
        void SortVec(std::vector<TreeNode>&, long );
        void InsertNode(std::vector<TreeNode>&, TreeNode, long);
        std::string Encode(const std::string&,int=1);
        void CreateList(std::vector<TreeNode>&,const std::string&);
        TreeNode* CreateTree(std::vector<TreeNode>&);
        void CreateTable(std::map<std::string,std::string>&, TreeNode*, const std::string&);
        std::string Decode(const std::string*);
        void RunTree(TreeNode* ,std::string&, std::string&, long* );
};


static int Dividition=1;
struct Huffman::Node{
public:
    bool operator>(Node other) const{
        return this->quantity>other.quantity;
    };
    bool operator<(Node other) const{
        return this->quantity<other.quantity;
    };
    bool operator==(Node other) const{
        return this->quantity==other.quantity;
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
};

struct Huffman::TreeNode:Node{
    TreeNode(TreeNode* left,TreeNode* rigth);
    TreeNode();
    bool isLeaf() const{
        return left == rigth;
    };
    TreeNode* left= nullptr;
    TreeNode* rigth= nullptr;
};




#endif //TEC_FILE_SYSTEM_HUFFMAN_H
