#ifndef CITY_H
#define CITY_H
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
#include "Glissor.h"


class City
{
public:
    City();
    virtual ~City();
    void init(RenderWindow *app_get, View *view_get, int x_get, int y_get ,  int tile_size_x_get, int tile_size_y_get);
    void draw();
    void selected();
    int get_x();
    int get_y();
private:
    View *view1;
    RenderWindow *app;
    My_Sprite sprite;
    int x, y, type, tile_size_x, tile_size_y;
    My_Text name;
};

#endif // CITY_H
