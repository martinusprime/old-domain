#include "My_Text.h"
#include <stdint.h>

Font My_Text::font1;

My_Text::My_Text()
{
    //ctor
}

My_Text::My_Text(const My_Text &other)
{
    m_app = other.m_app;
    event = other.event;
    texture = other.texture;
    sprite = other.sprite;
    text1 = other.text1;
    current_color = other.current_color;
}

void My_Text::init(RenderWindow *app, std::string content, int character_size, bool color)
{
    m_app = app;
    if(!texture.loadFromFile("ressources/menu_background.png"))
    {

    }
    if(My_Text::font1.loadFromFile("ressources/font2.ttf"))
    {
        if(color)
        {
            current_color = {255, 255, 255};

        }
        else
        {
            current_color = {0, 0, 0};

        }
        text1.setFont(My_Text::font1);
        text1.setString(content.c_str());
        text1.setCharacterSize(character_size);
        text1.setColor(current_color);
    }
    else
    {

    }
}

void My_Text::init(RenderWindow *app, std::string content, int character_size, bool color, int color_r,  int color_g, int color_b)
{
    m_app = app;
    if(font1.loadFromFile("ressources/font2.ttf"))
    {
        current_color = {
			static_cast<uint8_t>(color_r), static_cast<uint8_t>(color_g), static_cast<uint8_t>(color_b)};
        text1.setFont(font1);
        text1.setString(content.c_str());
        text1.setCharacterSize(character_size);
        text1.setColor(current_color);
    }
    else
    {

    }
}

void My_Text::draw(int x, int y, int character_size)
{
    text1.setPosition(x, y);
    text1.setCharacterSize(character_size);

    m_app->draw(text1);
}

void My_Text::refill(std::string content)
{
    text1.setString(content.c_str());
}

void My_Text::change_font(std::string font_file)
{
    font1.loadFromFile(font_file);
    text1.setFont(font1);
}
