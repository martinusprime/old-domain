#include "My_Text.h"

Font My_Text::font1;

My_Text::My_Text()
{
    //ctor
}

My_Text::My_Text(const My_Text &text_get)
{
    app = text_get.app;
    event = text_get.event;
    texture = text_get.texture;
    sprite = text_get.sprite;
    text1 = text_get.text1;
    current_color = text_get.current_color;
}

My_Text::~My_Text()
{
    //dtor
}

void My_Text::init(RenderWindow *app_get, string content, int character_size, bool color)
{
    app = app_get;
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
void My_Text::init(RenderWindow *app_get, string content, int character_size, bool color, int color_r,  int color_g, int color_b)
{
    app = app_get;
    if(font1.loadFromFile("ressources/font2.ttf"))
    {
        current_color = {color_r, color_g, color_b};
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

    app->draw(text1);
}
void My_Text::refill(string content)
{
    text1.setString(content.c_str());
}

void My_Text::change_font(string font_file)
{
    font1.loadFromFile(font_file);
    text1.setFont(font1);
}
