#ifndef GLISSOR_H
#define GLISSOR_H
#pragma once
#include <SFML/Graphics.hpp>
#include <sstream>
#include <iostream>
#include <cstdlib>
#include <string>
#include <cmath>
#include "Menu.h"
#include "My_Sprite.h"



class Glissor
{
public:
    Glissor();
    virtual ~Glissor();
    void draw();
    void update(int x_get, int y_get);
    void init(RenderWindow *app_get, int x_get, int y_get, int , int, View *view1_get);
protected:
private:
    View *view1;
    RenderWindow *app;
    My_Sprite bar, cursor_bar;
    int x, y, value, window_x, window_y;
    bool mouse_on;
    Vector2f a;
    Vector2i mouse_vec ;
    stringstream ss;
    My_Text rate;
};

#endif // GLISSOR_H
