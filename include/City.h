
#pragma once
#include <SFML/Graphics.hpp>
#include <sstream>
#include <iostream>
#include <cstdlib>
#include <string>
#include <cmath>
#include "Menu.h"
#include "My_Sprite.h"
#include "My_Text.h"


class City
{
public:
    City(RenderWindow *app, View *view, int x, int y, int tile_size_x, int tile_size_y);
    virtual ~City() = default;
    void create_city();
    void draw();
    int get_x();
    int get_y();
    void selected();
    
private:
    View *m_view1;
    RenderWindow *m_app;
    My_Sprite m_sprite;
    int m_x, m_y;
    int m_type, m_tile_size_x, m_tile_size_y;
    My_Text m_name;
};