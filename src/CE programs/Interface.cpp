//
// Created by diegoubuntu on 21/6/21.
//


#include "Interface.h"
#include "CEROBOT.h"
#include "CESEARCH.h"
#include "InputBox.h"
#include <string>

Interface::Interface() = default;

void Interface::show(){
    /*----------------DECLARE AND ASSIGN IMAGES-----------------*/
    Texture background;
    Texture btnSearch;
    Texture btnFile;

    if(!background.loadFromFile("src/CE programs/TFSBACKGROUND.png")){
        cout<<"Error to charge image";
    }
    if(!btnFile.loadFromFile("src/CE programs/btnCEROBOT.png")){
        cout<<"Error to charge image";
    }
    if(!btnSearch.loadFromFile("src/CE programs/btnSEARCH.png")){
        cout<<"Error to charge image";
    }
    Font font;
    if (!font.loadFromFile("src/CE programs/Fonts/Ubuntu-Bold.ttf"))
    {
        cout<<"Error to charge font";
    }

    /*----------------Instances-----------------*/
    CESEARCH CESEARCH;
    CEROBOT CEROBOT;

    /*----------------Blockers-----------------*/
    Sprite sprbackground;
    Sprite sprbtnSearch;
    Sprite sprbtnFile;

    sprbackground.setTexture(background);
    sprbtnFile.setTexture(btnFile);
    sprbtnFile.setPosition(300,250);

    sprbtnSearch.setTexture(btnSearch);
    sprbtnSearch.setPosition(1200,250);



  RenderWindow window(VideoMode(1920,846), "TEC FILE SYSTEM");
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
            }if (sprbtnSearch.getGlobalBounds().contains(translated_pos)) {
                if (event.type == Event::MouseButtonPressed) {
                    window.close();
                    CESEARCH.show();
                }
		    }if (sprbtnFile.getGlobalBounds().contains(translated_pos)) {
                if (event.type == Event::MouseButtonPressed) {
                    window.close();
                    CEROBOT.show();
            }
        }

        window.clear(Color::Transparent);
        window.draw(sprbackground);
        window.draw(sprbtnFile);
        window.draw(sprbtnSearch);
		window.display();
	}
}
