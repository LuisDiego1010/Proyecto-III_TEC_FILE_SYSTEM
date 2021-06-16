//
// Created by isaac on 15/6/21.
//

#include "Huffman.h"
#include <vector>
#include <iostream>
Node::Node() {
    quantity=0;
}
std::string Encode(const std::string& msg){
 std::vector<Node> Nodes;

    for (char i : msg) {
        for (int j = 0; j < Nodes.size()+1; ++j) {
            if(j+1>=Nodes.size()){
                auto tmp=Node();
                tmp.character=i;
                tmp.quantity=1;
                Nodes.insert(Nodes.begin(),tmp);
                break;
            }else{
                if(Nodes[j].character==i){
                    Nodes[j].quantity++;
                    if (j+1==Nodes.size()){
                        break;
                    }
                    for (int k = j; k+1 < Nodes.size(); ++k) {
                        if (Nodes[k]>Nodes[k+1]){
                            auto tmpN=Nodes[k];
                            Nodes[k]=Nodes[k+1];
                            Nodes[k+1]=tmpN;
                        }else{
                            break;
                        }
                    }

                    break;
                }else{
                        continue;
                    }
                }
        }
    }
    for (Node a:Nodes) {
        std::cout<<a.quantity;
        std::cout<<a.character;
        std::cout<<std::endl;



    }
return msg;
}


