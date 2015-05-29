#ifndef MY_WINDOW_H
#define MY_WINDOW_H
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
    My_window();
    virtual ~My_window();
    void draw();
    void init(RenderWindow *app_get,string name_get, float width, float height,int x_get, int y_get, View *view1_get,int screen_x_get, int screen_y_get);
    void add_glissor(int x, int y);
    void add_button(int x, int y);
    void update();
    void activate();
    int get_glissor(int glissor_number_get);
    void desactivate();
    bool is_activated();
protected:
private:
    View *view1;
    RenderWindow *app;
    My_Sprite window_sprite, grip_bar;
    Vector2f mouse_save_vec;
    int w, h,screen_y, screen_x, x, y, glissor_number, button_number, window_w, window_h;
    My_Text name;
    vector<Glissor> glissors;
    Button button[10];
    Button cross;
    bool activation, moving;
};

#endif // MY_WINDOW_H
