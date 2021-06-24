//
// Created by diegoubuntu on 21/6/21.
//

#include "CESEARCH.h"
#include "InputBox.h"
#include "TextBox.h"
#include "Interface.h"
#include <nlohmann/json.hpp>

CESEARCH::CESEARCH() = default;

void CESEARCH::show() {
    //Initialice Socket
    Socket.Init();
    Texture backgroundCESEARCH2;
    Texture btnCESEARCH2;
    Texture btnmenu;
    std::string a;
    nlohmann::basic_json<> tmp;
    tmp["name"]="";
    tmp["operation"]=2;
    a=Socket.comunicatte(to_string(tmp));
    tmp= nlohmann::basic_json<>::parse(a);
    std::vector<std::string> master;
    std::vector<std::string> filtered;



    if(!backgroundCESEARCH2.loadFromFile("src/CE programs/backgroundCESEARCH.png")){
        cout<<"Error to charge image";
    }

    if(!btnCESEARCH2.loadFromFile("src/CE programs/btnCESEARCH2.png")){
        cout<<"Error to charge image";
    }

    if(!btnmenu.loadFromFile("src/CE programs/sprmenu.png")){
        cout<<"Error to charge image";
    }

    Font font;
    if (!font.loadFromFile("src/CE programs/Fonts/Ubuntu-Bold.ttf"))
    {
        cout<<"Error to charge font";
    }

    Sprite sprbackgroundCESEARCH;
    sprbackgroundCESEARCH.setTexture(backgroundCESEARCH2);
    sprbackgroundCESEARCH.setPosition(0, 0);

    Sprite sprbtnSearch2;
    sprbtnSearch2.setTexture(btnCESEARCH2);
    sprbtnSearch2.setPosition(400, 250);

    Sprite sprMenu;
    sprMenu.setTexture(btnmenu);
    sprMenu.setPosition(1800, 950);

    InputBox searchbox (Vector2f(550,30));
    searchbox.setPosition(600, 270);

    TextBox textbox(Vector2f(400,330));
    textbox.setPosition(100, 270);

    Interface mainInterface;

    RenderWindow window(VideoMode(1920, 1080), "CESEARCH");
    while (window.isOpen())
    {
        Event event;
        auto mouse_pos = sf::Mouse::getPosition(window); // Mouse position relative to the window
        auto translated_pos = window.mapPixelToCoords(mouse_pos); // Mouse position translated into world coordinates
        while (window.pollEvent(event)){
            if (event.type == Event::Closed){
                window.close();

            }if (event.type == Event::MouseButtonPressed) {
                if (sprbtnSearch2.getGlobalBounds().contains(translated_pos)) {
                    if (searchbox.text!=""){
                        setNameSearchBook(searchbox.text);
                        cout<<"SE ESTA BUCANDO EL LIBRO CON EL NOMBRE: "<<nameSearchBook;
                        nlohmann::basic_json<> Json;
                        Json["name"]=nameSearchBook;
                        Json["operation"]=1;
                        std::string data= Socket.comunicatte(to_string(Json));
                        textbox.PrintScreen(data);
                    }
                }
                if (sprMenu.getGlobalBounds().contains(translated_pos)) {
                    mainInterface.show();
                    window.close();
                    return;
                }else{
                    searchbox.select(translated_pos);
                }
            }else if(event.type==Event::TextEntered) {
                searchbox.write(event);
                std::vector<std::string> list;
                std::string listString;
                for (const auto& c:master) {
                    if(c.find(searchbox.text)!=std::string::npos){
                        list.push_back(c);
                        listString+=c;
                    }
                }
                filtered=list;
            }
        }
        window.clear(Color::Transparent);
        window.draw(sprbackgroundCESEARCH);
        window.draw(searchbox);
        window.draw(sprMenu);
        window.draw(textbox);
        window.draw(sprbtnSearch2);
        window.display();
    }
}
string CESEARCH::setNameSearchBook(String name_Book) {
    CESEARCH::nameSearchBook = name_Book;
    return nameSearchBook;
}