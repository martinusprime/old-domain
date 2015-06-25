#pragma once

#include <SFML/Graphics.hpp>
#include <sstream>
#include <iostream>
#include <cstdlib>
#include <string>
#include <cmath>
#include "Menu.h"
#include "My_Sprite.h"



class Loading_bar
{
public:
    Loading_bar(RenderWindow *app, int x, int y, int window_x, int window_y, View *view1);
    /* copy-constructor */
    Loading_bar(const Loading_bar &Loading_bar);
    virtual ~Loading_bar() = default;
    void draw();
    void began();
    void update(int x, int y);
    float get_value();

private:
    View *m_view1;
    RenderWindow *m_app;
    My_Sprite m_bar, m_loading_bar;
    int m_x, m_y, m_window_x, m_window_y;
    float m_value;
    bool m_mouse_on;
    Vector2f m_a;
    Vector2i m_mouse_vec;
    My_Text m_rate;
    Clock m_clock;
};

