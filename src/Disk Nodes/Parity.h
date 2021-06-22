//
// Created by isaac on 21/6/21.
//

#ifndef TEC_FILE_SYSTEM_PARITY_H
#define TEC_FILE_SYSTEM_PARITY_H
#include <string>

std::string parityGenerator(const std::string& , bool evenParity=true);
std::string parityChecker(const std::string& , bool evenParity=true);

#endif //TEC_FILE_SYSTEM_PARITY_H
