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


class Button
{
public:
    Button(RenderWindow *app_get, string name_get, int x_get, int y_get, int window_x_get, int window_y_get, View *view1_get);
    Button(RenderWindow *app_get, bool, int window_x_get, int window_y_get, int window_w_get, View *view1_get); 
    virtual ~Button() = default;
    
    void draw();
    void update(int x_get, int y_get);
    bool is_activated();

private:
    View *m_view1;
    RenderWindow *m_app;
    My_Sprite button_sprite;
    int m_w, m_h, m_window_x, m_window_y, m_window_w,  m_x, m_y;
    My_Text m_name;
    bool mouse_on, mouse_click, cross, activation;
    Vector2f m_a;
    Vector2i mouse_vec;
};

