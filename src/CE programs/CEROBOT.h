//
// Created by diegoubuntu on 21/6/21.
//

#ifndef TEC_FILE_SYSTEM_CEROBOT_H
#define TEC_FILE_SYSTEM_CEROBOT_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include <SFML/Graphics/Color.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <filesystem>
#include <queue>
#include <vector>
using namespace sf;
using namespace std;


class CEROBOT {
public:
    string dirPath;
    vector<string> elementos;
    bool active;


    /**
 * @brief Constructor of class (DEFAULT)
 */
    CEROBOT();

/**
* @brief Responsible for displaying the configuration window.
*/
    void show();


    void list_dir(string dir);

    void init();

};


#endif //TEC_FILE_SYSTEM_CEROBOT_H
