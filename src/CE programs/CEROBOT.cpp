//
// Created by diegoubuntu on 21/6/21.
//

#include "CEROBOT.h"

CEROBOT::CEROBOT() = default;

void CEROBOT::show() {
    Texture backgroundCEROBOT2;
    Texture btnCEROBOT2;

    if(!backgroundCEROBOT2.loadFromFile("src/CE programs/backgroundCEROBOT.png")){
        cout<<"Error to charge image";
    }

    if(!btnCEROBOT2.loadFromFile("src/CE programs/btnCEROBOT2.png")){
        cout<<"Error to charge image";
    }

    Font font;
    if (!font.loadFromFile("src/CE programs/Fonts/Ubuntu-Bold.ttf"))
    {
        cout<<"Error to charge font";
    }

    Sprite sprbackgroundCEROBOT2;
    sprbackgroundCEROBOT2.setTexture(backgroundCEROBOT2);
    sprbackgroundCEROBOT2.setPosition(0, 0);

    Sprite sprbtnRobot2;
    sprbtnRobot2.setTexture(btnCEROBOT2);
    sprbtnRobot2.setPosition(1200, 250);

    RenderWindow window(VideoMode(1920, 1080), "TEC FILE SYSTEM");
    while (window.isOpen())
    {
        Event event;
        auto mouse_pos = sf::Mouse::getPosition(window); // Mouse position relative to the window
        auto translated_pos = window.mapPixelToCoords(mouse_pos); // Mouse position translated into world coordinates
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed){
                window.close();
            }
        }if (sprbtnRobot2.getGlobalBounds().contains(translated_pos)) {
            if (event.type == Event::MouseButtonPressed) {
                //LOGICA DE CEROBOT
            }
        }

        window.clear(Color::Transparent);
        window.draw(sprbackgroundCEROBOT2);
        window.draw(sprbtnRobot2);
        window.display();
    }
}