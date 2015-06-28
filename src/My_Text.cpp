#include "My_Text.h"
#include <stdint.h>

Font My_Text::m_font1;

My_Text::My_Text()
{
    //ctor
}

My_Text::My_Text(const My_Text &other)
{
    m_app = other.m_app;
    m_event = other.m_event;
    m_texture = other.m_texture;
    m_sprite = other.m_sprite;
    m_text1 = other.m_text1;
    m_current_color = other.m_current_color;
}

void My_Text::init(RenderWindow *app, std::string content, int character_size, bool color)
{
    m_app = app;
    
    m_content = content;

    if(My_Text::m_font1.loadFromFile("ressources/font2.ttf"))
    {
        if(color)
        {
            m_current_color = {255, 255, 255};

        }
        else
        {
            m_current_color = {0, 0, 0};

        }
        m_text1.setFont(My_Text::m_font1);
        m_text1.setString(content.c_str());
        m_text1.setCharacterSize(character_size);
        m_text1.setColor(m_current_color);
    }
   
}

void My_Text::init(RenderWindow *app, std::string content, int character_size, bool color, int color_r,  int color_g, int color_b)
{
    m_app = app;
    if(m_font1.loadFromFile("ressources/font2.ttf"))
    {
        m_current_color = {
		static_cast<uint8_t>(color_r), static_cast<uint8_t>(color_g), static_cast<uint8_t>(color_b)};
        m_text1.setFont(m_font1);
        m_text1.setString(content);
        m_text1.setCharacterSize(character_size);
        m_text1.setColor(m_current_color);
    }
    else
    {

    }
}

void My_Text::draw(int x, int y, int character_size)
{
    m_text1.setPosition(x, y);
    m_text1.setCharacterSize(character_size);

    m_app->draw(m_text1);
}

void My_Text::refill(std::string content)
{
    m_text1.setString(content);
}

void My_Text::change_font(std::string font_file)
{
    m_font1.loadFromFile(font_file);
    m_text1.setFont(m_font1);
}


String My_Text::get_text()
{
    return m_content;
}
