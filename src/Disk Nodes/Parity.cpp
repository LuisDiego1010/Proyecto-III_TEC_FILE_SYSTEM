//
// Created by isaac on 21/6/21.
//

#include "Parity.h"
std::string parityGenerator(const std::string& word, bool evenParity){
    for(char a:word){
        unsigned int letter=(unsigned int)((unsigned char)a);
        if(letter%2==1){
            evenParity=!evenParity;
        }
        letter=letter>>(1);

        if(letter%2==1){
            evenParity=!evenParity;
        }
        letter=letter>>(1);

        if(letter%2==1){
            evenParity=!evenParity;
        }
        letter=letter>>(1);

        if(letter%2==1){
            evenParity=!evenParity;
        }
        letter=letter>>(1);

        if(letter%2==1){
            evenParity=!evenParity;
        }
        letter=letter>>(1);

        if(letter%2==1){
            evenParity=!evenParity;
        }
        letter=letter>>(1);

        if(letter%2==1){
            evenParity=!evenParity;
        }
        letter=letter>>(1);

        if(letter%2==1){
            evenParity=!evenParity;
        }
    }
    if (!evenParity){
        return word+std::string("1");
    }else{
        return word+std::string("0");
    }
}

std::string parityChecker(const std::string& stream, bool evenParity){
    bool parity= false;

    for (int i = 0; i < stream.size()-1; ++i) {
        int letter = (int) ((unsigned char) stream[i]);
        if (letter % 2 == 1) {
            parity = !parity;
        }
        letter=letter >> (1);

        if (letter % 2 == 1) {
            parity = !parity;
        }
        letter=letter >> (1);

        if (letter % 2 == 1) {
            parity = !parity;
        }
        letter=letter >> (1);

        if (letter % 2 == 1) {
            parity = !parity;
        }

        letter=letter >> (1);

        if (letter % 2 == 1) {
            parity = !parity;
        }

        letter=letter >> (1);

        if (letter % 2 == 1) {
            parity = !parity;
        }

        letter=letter >> (1);

        if (letter % 2 == 1) {
            parity = !parity;
        }

        letter=letter >> (1);

        if (letter % 2 == 1) {
            parity = !parity;
        }
    }
    if(stream.substr(stream.size()-1,1)==std::string("1")){
        parity = !parity;
    }
    if(parity==evenParity){
        return std::string("-2");
    }
    return stream.substr(0,stream.size()-1);
}