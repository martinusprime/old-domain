#ifndef BUILDING_H
#define BUILDING_H
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
    Building();
    virtual ~Building();
    void init(RenderWindow *app_get, View *view_get,int type_get);
    void draw(int x_get, int y_get);
    void draw();
    void selected();
    int get_x();
    int get_y();
private:
    View *view1;
    RenderWindow *app;
    My_Sprite sprite;
    int x, y, type;
};

#endif // BUILDING_H
