//
// Created by diegoubuntu on 21/6/21.
//

#include "CESEARCH.h"

CESEARCH::CESEARCH() = default;

void CESEARCH::show() {
    Texture backgroundCESEARCH2;
    Texture btnCESEARCH2;

    if(!backgroundCESEARCH2.loadFromFile("src/CE programs/backgroundCESEARCH.png")){
        cout<<"Error to charge image";
    }

    if(!btnCESEARCH2.loadFromFile("src/CE programs/btnCESEARCH2.png")){
        cout<<"Error to charge image";
    }

    Font font;
    if (!font.loadFromFile("src/CE programs/Fonts/Ubuntu-Bold.ttf"))
    {
        cout<<"Error to charge font";
    }

    Sprite sprbackgroundCESEARCH;
    sprbackgroundCESEARCH.setTexture(btnCESEARCH2);
    sprbackgroundCESEARCH.setPosition(0, 0);

    Sprite sprbtnSearch2;
    sprbtnSearch2.setTexture(btnCESEARCH2);
    sprbtnSearch2.setPosition(1200, 250);

    RenderWindow window(VideoMode(1920, 1080), "CESEARCH");
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
        }if (sprbtnSearch2.getGlobalBounds().contains(translated_pos)) {
            if (event.type == Event::MouseButtonPressed) {
                //LOGICA DE CESEARCH
            }
        }

        window.clear(Color::Transparent);
        window.draw(sprbackgroundCESEARCH);
        window.draw(sprbtnSearch2);
        window.display();
    }
}