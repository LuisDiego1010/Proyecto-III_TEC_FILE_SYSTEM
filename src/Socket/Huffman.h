//
// Created by isaac on 15/6/21.
//

#ifndef TEC_FILE_SYSTEM_HUFFMAN_H
#define TEC_FILE_SYSTEM_HUFFMAN_H

#include <string>
#include <vector>
#include <map>
namespace Huffman{
        /**
         * @brief to storage the quantity and char and provide operators for functions
         */
        struct Node;
        /**
         * @brief to estructure the huffman Node.
         */
        struct TreeNode;

        /**
         * @brief function to sort a vector as a array to keep the tree.
         */
        void SortVec(std::vector<TreeNode>&, long );

        /**
         * @brief Insert Node in the huffman Tree.
         */
        void InsertNode(std::vector<TreeNode>&, TreeNode, long);

        /**
         * @brief Encode with Hufmann a string.
         * @return
         */
        std::string Encode(const std::string&,int=1);
        /**
         * @brief Create the list with the probability of char
         */
        void CreateList(std::vector<TreeNode>&,const std::string&);
        /**
         * @brief Create a tree using the list sorted with probabilitys
         * @return
         */
        TreeNode* CreateTree(std::vector<TreeNode>&);
        /**
         * @brief create the representation table using the tree
         */
        void CreateTable(std::map<std::string,std::string>&, TreeNode*, const std::string&);
        /**
         * @brief Decode a huffman algorith
         * Recieve a Json wiht the comprimed data and a map (dictionarie ) with the probabilities
         * @return
         */
        std::string Decode(const std::string*);
        /**
         * @brief Check te code huffman and decode the representation to a string.
         */
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
