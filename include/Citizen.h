#ifndef CITIZEN_H
#define CITIZEN_H
#pragma once

#include <SFML/Graphics.hpp>
#include <sstream>
#include <iostream>
#include <cstdlib>
#include <string>
#include <cmath>

#include "Grid.h"
#include "Menu.h"
#include "My_Sprite.h"
#include "Sprite_Creator.h"

class Citizen
{
public:
    Citizen();
    virtual ~Citizen();
    void init(RenderWindow *app_get, View *view_get);
    void draw();
    void select();
    bool is_selected();
    void set_path(int x_path, int y_path, int path_id);
    void update();
    void on_city();
    bool is_on_city();
    bool get_goal();
    void is_over_city();
    int get_x();
    int get_y();
    void set_goal(int goal_x_get , int goal_y_get);
    Sprite get_sprite();
protected:
private:
    View *view1;
    RenderWindow *app;
    Event event;
    bool is_goal, selection, over_city;
    Clock move_clock;
    Time elapsed_move;
    My_Sprite sprite;
    My_Sprite goal_sprite;

    Sprite_Creator sprite_creator1;

    int x, y, goal_x, goal_y, path_place, path_number;
    int path[100][2];
    Tile over_tile;
    //CITIZEN INFO
    string name;
    int age;

};

#endif // CITIZEN_H
