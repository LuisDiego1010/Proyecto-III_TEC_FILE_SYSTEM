/**
  * @file InputBox.h
  * */

#ifndef PROYECTO_II_INPUTBOX_H
#define PROYECTO_II_INPUTBOX_H
#include <SFML/Graphics.hpp>

using namespace sf;
using namespace std;
class InputBox : public sf::Drawable{
private:
    virtual void draw(RenderTarget& target, RenderStates states)const;

public:
    /**
     * Charge a default font to the INput box and auto determine the text size
     * the size of the InputBox can`t be changed after.
     * @param size
     */
    explicit InputBox(Vector2f size);
    static sf::Font font;
    static bool LFont;

public:
    RectangleShape rectangle;
    string text;
    Text print;
    int x;
    int y;
    bool selected;

    /**
     * Set the position of the BOX
     * @param x
     * @param y
     */
    void setPosition(int x, int y);
    /**
     * Expected to be in the event mouse click
     * determine if the mouse have clicked in the input box
     * @param point
     */
    void select(Vector2<float> point);
    /**
     * Expect3ed to be in the event inpuet text
     * get the event and if sleceted is True write the event text in the box
     * @param event
     */
    void write(Event event);

    /**
     * @brief In charge of print the file in the text
    */
    void PrintScreen(std::string="");
};


#endif //PROYECTO_II_INPUTBOX_H
