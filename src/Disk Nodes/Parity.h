//
// Created by isaac on 21/6/21.
//

#ifndef TEC_FILE_SYSTEM_PARITY_H
#define TEC_FILE_SYSTEM_PARITY_H
#include <string>
/**
 * Append 0 or 1 in a string to establish it parity.
 * @param evenParity =true, oddparity =false;
 * @return same string with bit parity
 */
std::string parityGenerator(const std::string& , bool evenParity=true);
/**
 * check 0 or 1 in the end of a string to establish if respect parity.
 * @param evenParity =true, oddparity =false;
 * @return same string without bit parity
 */
std::string parityChecker(const std::string& , bool evenParity=true);

#endif //TEC_FILE_SYSTEM_PARITY_H
