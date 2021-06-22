//
// Created by diegoubuntu on 21/6/21.
//

#ifndef TEC_FILE_SYSTEM_CESEARCH_H
#define TEC_FILE_SYSTEM_CESEARCH_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <filesystem>

using namespace sf;
using namespace std;

class CESEARCH {
public:
/**
 * @brief Constructor of class (DEFAULT)
 */
     CESEARCH();

/**
* @brief Responsible for displaying the configuration window.
*/
    void show();
};


#endif //TEC_FILE_SYSTEM_CESEARCH_H
