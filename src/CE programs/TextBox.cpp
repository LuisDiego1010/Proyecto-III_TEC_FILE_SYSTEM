//
// Created by isaac on 24/6/21.
//

#include "TextBox.h"

#include <iostream>
#include <utility>

using namespace sf;
using namespace std;
bool TextBox::LFont=false;
sf::Font TextBox::font;

void TextBox::draw(RenderTarget &target, RenderStates states) const {
    target.draw(rectangle);
    for (const auto& a:print) {
        target.draw(a);
    }
}

TextBox::TextBox(Vector2f size) {
    if(!LFont){
        LFont=TextBox::font.loadFromFile("src/CE programs/Fonts/Ubuntu-Bold.ttf");
    }
    rectangle=RectangleShape(size);
}

void TextBox::setPosition(int x, int y) {
    rectangle.setPosition(x,y);
    this->x=x;
    this->y=y;
}

void TextBox::PrintScreen(std::string toPrint) {
    text=std::move(toPrint);
    print.clear();
    u_long split=rectangle.getSize().x/(10);
    for (int i = 0; i < text.size(); ++i) {
        u_long line=text.find('\n');
        std::string tmpstring;
        if(split>line){
            split=line;
            tmpstring=text.substr(0,split);
            split++;
        }else{
            tmpstring=text.substr(0,split);
        }
        if(split<text.size()){
            text=text.substr(split);
        }else{
            text="";
        }
        auto tmp=Text(tmpstring, TextBox::font, 18);
        tmp.setFillColor(sf::Color::Black);
        tmp.setPosition(x,y+i*15+2);
        print.push_back(tmp);
    }
}