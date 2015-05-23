#ifndef BUTTON_H
#define BUTTON_H
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
        Button();
        virtual ~Button();
        void draw();
        void init(RenderWindow *app_get,string name_get, int x_get, int y_get, int window_x_get, int window_y_get, View *view1_get);
        void init(RenderWindow *app_get,bool, int window_x_get, int window_y_get,int window_w_get,  View *view1_get);
        void update(int x_get, int y_get);
        bool is_activated();
    protected:
    private:
        View *view1;
        RenderWindow *app;
        My_Sprite button_sprite;
        int w, h, window_x, window_y,window_w,  x, y;
        My_Text name;
        bool mouse_on, mouse_click, cross, activation;
        Vector2f a;
        Vector2i mouse_vec ;
        stringstream ss;
};

#endif // BUTTON_H
