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
#include "Button.h"


class My_window
{
public:
    My_window(RenderWindow *app_get, string name_get, float width, float height, int x, int y, View *view1_get, int screen_x_get, int screen_y_get);
    virtual ~My_window() = default;
    void draw();
    void add_glissor(int x, int y);
    void add_image(int x, int y, string path);
    void add_button(int x, int y);
    void update();
    void activate();
    int get_glissor(int glissor_number_get);
    void desactivate();
    bool is_activated();
protected:
private:
    View *m_view1;
    RenderWindow *m_app;
    My_Sprite window_sprite, grip_bar;
    Vector2f mouse_save_vec;
    int m_w, m_h;
    int m_screen_y, m_screen_x;
    int m_x, m_y;
    int window_w, window_h;
    My_Text m_name;
    vector<Glissor> glissors;
    vector<My_Sprite> sprites;
    vector<Button> m_buttons;
    Button m_cross;
    bool activation, moving;
};

