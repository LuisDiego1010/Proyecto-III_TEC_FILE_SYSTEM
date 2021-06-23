//
// Created by diegoubuntu on 21/6/21.
//

#include "CEROBOT.h"
#include "Interface.h"
#include <iostream>
#include <dirent.h>
#include "InputBox.h"

using namespace std;

CEROBOT::CEROBOT() = default;


void CEROBOT::list_dir(string dir) {
    DIR *directorio;
    struct dirent *elemento;
    string elem;

    int i=0;
    if (directorio = opendir(dir.c_str())) {
        while (elemento = readdir(directorio)) {
            elem = elemento->d_name;
            if (elem != "." && elem != ".."){
                elementos.push_back(elem);
                i++;
                cout << elem << endl;
            }
        }
    }
    closedir(directorio);
}

void CEROBOT::init() {
    list_dir(dirPath);
}

void CEROBOT::show() {
    Texture backgroundCEROBOT2;
    Texture btnCEROBOT2;
    Texture btnmenu;

    InputBox Dirbox(Vector2f(550, 30));
    Dirbox.setPosition(600, 270);
    InputBox Resultsbox(Vector2f(550, 550));
    Resultsbox.setPosition(600, 370);

    if (!backgroundCEROBOT2.loadFromFile("src/CE programs/backgroundCEROBOT.png")) {
        cout << "Error to charge image";
    }

    if (!btnCEROBOT2.loadFromFile("src/CE programs/btnCEROBOT2.png")) {
        cout << "Error to charge image";
    }

    if (!btnmenu.loadFromFile("src/CE programs/sprmenu.png")) {
        cout << "Error to charge image";
    }

    Font font;
    if (!font.loadFromFile("src/CE programs/Fonts/Ubuntu-Bold.ttf")) {
        cout << "Error to charge font";
    }

    Sprite sprbackgroundCEROBOT2;
    sprbackgroundCEROBOT2.setTexture(backgroundCEROBOT2);
    sprbackgroundCEROBOT2.setPosition(0, 0);

    Sprite sprbtnRobot2;
    sprbtnRobot2.setTexture(btnCEROBOT2);
    sprbtnRobot2.setPosition(1200, 250);

    Sprite sprMenu;
    sprMenu.setTexture(btnmenu);
    sprMenu.setPosition(1700, 950);

    Interface mainInterface;

    bool active = false;
    RenderWindow window(VideoMode(1920, 1080), "TEC FILE SYSTEM");
    while (window.isOpen()) {
        Event event;
        auto mouse_pos = sf::Mouse::getPosition(window); // Mouse position relative to the window
        auto translated_pos = window.mapPixelToCoords(mouse_pos); // Mouse position translated into world coordinates
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed) {
                window.close();
            } else if (event.type == Event::MouseButtonPressed) {
                if (sprbtnRobot2.getGlobalBounds().contains(translated_pos)) {
                    if (event.type == Event::MouseButtonPressed) {

                        if (Dirbox.text != "") {
                            dirPath = Dirbox.text;
                            active = true;
                            if (active == true) {
                                init();
                                active = false;cout<<"----------------------------"<<endl;
                                for(int i=0;i<elementos.size();i++){
                                    Resultsbox.text = elementos.front().data();
                                    cout<<elementos[i].data()<<endl;

                                }
                                cout<<"----------------------------"<<endl;


                            }

                        }


                    }
                }
                if (sprMenu.getGlobalBounds().contains(translated_pos)) {
                    mainInterface.show();
                    window.close();
                    return;
                } else {
                    Dirbox.select(translated_pos);
                }
            } else if (event.type == Event::TextEntered) {

                Dirbox.write(event);

            }
        }
        window.clear(Color::Transparent);
        window.draw(sprbackgroundCEROBOT2);
        window.draw(sprMenu);
        window.draw(Dirbox);
        window.draw(Resultsbox);
        window.draw(sprbtnRobot2);
        window.display();
    }
}