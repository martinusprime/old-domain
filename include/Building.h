#pragma once

#include <SFML/Graphics.hpp>
#include <sstream>
#include <iostream>
#include <cstdlib>
#include <string>
#include <cmath>
#include "Menu.h"
#include "My_Sprite.h"
#include "Glissor.h"



class Building
{
public:
    Building(RenderWindow *app_get, View *view_get, int type_get);
    virtual ~Building() = default;
    void draw(int x_get, int y_get);
    void draw();
    void selected();
    int get_x();
    int get_y();

private:
    View *m_view1;
    RenderWindow *m_app;
    My_Sprite m_sprite;
    int m_x, m_y, m_type;
};


