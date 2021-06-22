//
// Created by isaac on 11/5/21.
//

#include <iostream>
#include "InputBox.h"
using namespace sf;
using namespace std;
bool InputBox::LFont=false;
sf::Font InputBox::font;

void InputBox::draw(RenderTarget &target, RenderStates states) const {
    target.draw(rectangle);
    target.draw(print);
}

InputBox::InputBox(Vector2f size) {
    if(!LFont){
        LFont=InputBox::font.loadFromFile("src/CE programs/Fonts/Ubuntu-Bold.ttf");
    }
    rectangle=RectangleShape(size);
    print=Text(text, InputBox::font, size.y-2);
    print.setFillColor(sf::Color::Black);
}

void InputBox::setPosition(int x, int y) {
    rectangle.setPosition(x,y);
    print.setPosition(x,y);
    this->x=x;
    this->y=y;
}

void InputBox::select(Vector2<float> point) {
    if(rectangle.getGlobalBounds().contains(point)){
        selected=true;
    }else{
        selected= false;
    }
}

void InputBox::write(Event event) {

    if(!selected){
        return;
    }

    if(event.key.code==8){
        if(!text.empty()){
            text.pop_back();

            print.setString(text);
        }
        return;

    }
    text+=event.text.unicode;

    print.setString(text);

}







