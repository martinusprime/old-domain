#pragma once

#include <string>
#include <SFML/Graphics.hpp>
using namespace sf;

class My_Text
{
public:
    My_Text();
    /* copy constructor */
    My_Text(const My_Text &text);
    virtual ~My_Text() = default;
    void init(RenderWindow *app, std::string content, int character_size, bool color);
    void init(RenderWindow *app, std::string content, int character_size, bool color, int color_r,  int color_g, int color_b);
    void draw(int x, int y, int character_size);
    String get_text();
    void refill(std::string content);
    void change_font(std::string font_file);

private:
    RenderWindow *m_app;
    Event m_event;
    Texture m_texture;
    Sprite m_sprite;
    //can not be destroyed (see sf::Text documentation)
    static Font m_font1;
    Text m_text1;
    String m_content;
    Color m_current_color;
};


