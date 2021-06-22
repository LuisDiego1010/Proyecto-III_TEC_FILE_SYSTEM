//
// Created by diegoubuntu on 21/6/21.
//

#ifndef TEC_FILE_SYSTEM_INTERFACE_H
#define TEC_FILE_SYSTEM_INTERFACE_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <filesystem>

using namespace sf;
using namespace std;

class Interface {
public:
    /**
     * @brief Constructor class (DEFAULT)
     */
    Interface();

    /**
    * @brief Constructor class
    */
    void show ();
};

#endif //TEC_FILE_SYSTEM_INTERFACE_H
