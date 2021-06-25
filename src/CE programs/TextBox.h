//
// Created by isaac on 24/6/21.
//

#ifndef TEC_FILE_SYSTEM_TEXTBOX_H
#define TEC_FILE_SYSTEM_TEXTBOX_H
#include <SFML/Graphics.hpp>

using namespace sf;
using namespace std;

class TextBox : public sf::Drawable{
    private:
    virtual void draw(RenderTarget& target, RenderStates states)const;

public:
    /**
     * Charge a default font to the Text and create the white space.
     * @param size
     */
    explicit TextBox(Vector2f size);
    static sf::Font font;
    static bool LFont;

public:
    RectangleShape rectangle;
    string text;
    std::vector< Text> print;
    int x{};
    int y{};

    /**
     * Set the position of the BOX
     * @param x
     * @param y
     */
    void setPosition(int x, int y);

    /**
     * @brief In charge of print the string in the window
    */
    void PrintScreen(std::string="");
};


#endif //TEC_FILE_SYSTEM_TEXTBOX_H
