//
// Created by diegoubuntu on 21/6/21.
//


#include "Interface.h"
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

    sf::Font font;
    if (!font.loadFromFile("src/CE programs/Fonts/Ubuntu-Bold.ttf"))
    {
        cout<<"Error to charge font";
    }
    /*----------------Blockers-----------------*/
    Sprite sprbackground;
    Sprite sprbtnSearch;
    Sprite sprbtnFile;

    sprbackground.setTexture(background);
    sprbtnFile.setTexture(btnFile);
    sprbtnFile.setPosition(300,250);

    sprbtnSearch.setTexture(btnSearch);
    sprbtnSearch.setPosition(1200,250);

    InputBox searchbox=InputBox(Vector2f(500,30));
    searchbox.setPosition(1200, 780);

  RenderWindow window(VideoMode(1920, 1080), "TEC FILE SYSTEM");
  	while (window.isOpen())
	{
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
				window.close();
		}
        window.clear(Color::Transparent);
        window.draw(sprbackground);
        window.draw(sprbtnFile);
        window.draw(sprbtnSearch);
        window.draw(searchbox);
		window.display();
	}
}
