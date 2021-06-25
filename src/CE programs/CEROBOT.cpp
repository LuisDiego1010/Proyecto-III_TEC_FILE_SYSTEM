//
// Created by diegoubuntu on 21/6/21.
//

#include "CEROBOT.h"
#include "Interface.h"
#include <iostream>
#include <dirent.h>
#include <fstream>
#include <nlohmann/json.hpp>
#include "InputBox.h"

using namespace std;

CEROBOT::CEROBOT() = default;


void CEROBOT::list_dir(string dir) {
    DIR *directorio;
    struct dirent *elemento;
    string elem;

    int i = 0;
    if (directorio = opendir(dir.c_str())) {
        while (elemento = readdir(directorio)) {
            elem = elemento->d_name;
            if (elem != "." && elem != "..") {
                elementos.push_back(elem);
                i++;
                //cout << elem << endl;
            }
        }
    }
    closedir(directorio);
}

void CEROBOT::init() {
    list_dir(dirPath);
    active = true;
    Socket.Init();
}

void CEROBOT::show() {
    Texture backgroundCEROBOT2;
    Texture btnCEROBOT2;
    Texture btnmenu;

    InputBox Resultsbox(Vector2f(1920, 30));
    Resultsbox.setPosition(0, 370);

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
    sprbtnRobot2.setPosition(200, 250);

    Sprite sprMenu;
    sprMenu.setTexture(btnmenu);
    sprMenu.setPosition(1750, 950);

    Interface mainInterface;

    active = false;
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
                        char *file = new char[150];
                        FILE *direc = popen("zenity --file-selection --directory", "r");
                        fgets(file, 150, direc);
                        string fileDir(file);
                        delete file;
                        fileDir.pop_back();
                        dirPath = fileDir;
                        init();
                        if (active == true) {
                            string a = "";
                            for (int i = 0; i < elementos.size(); i++) {
                                std::ifstream in(dirPath + "/" + elementos[i]);
                                if (!in.good()) {

                                }
                                in.seekg(0, in.end);
                                int pos = in.tellg();
                                string tmp("", pos);
                                in.seekg(0, in.beg);
                                in.read(tmp.data(), pos);
                                if(((int)tmp[0]==(-17)&&(int)tmp[1]==(-69)&&(int)tmp[2]==(-65))){
                                    tmp=tmp.substr(3);
                                }
                                nlohmann::basic_json<> Json;
                                Json["data"]=tmp;
                                Json["name"]=elementos[i];
                                Json["operation"]=0;
                                Socket.comunicatte(to_string(Json));
                                cout << elementos[i] << endl;
                                a += elementos[i];
                                a += "     ";
                            }
                            Resultsbox.PrintScreen(a);
                            active = false;
                        }
                    }
                }
                if (sprMenu.getGlobalBounds().contains(translated_pos)) {
                    window.close();
                    mainInterface.show();
                   return;
                }
            }
        }
        window.clear(Color::Transparent);
        window.draw(sprbackgroundCEROBOT2);
        window.draw(sprMenu);
        window.draw(Resultsbox);
        window.draw(sprbtnRobot2);
        window.display();
    }
}

void CEROBOT::Start() {
    Socket.Init();

}


