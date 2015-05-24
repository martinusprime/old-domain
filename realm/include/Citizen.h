#ifndef CITIZEN_H
#define CITIZEN_H
#pragma once
#include <SFML/Graphics.hpp>
#include <sstream>
#include <iostream>
#include <cstdlib>
#include <string>
#include <cmath>
#include "Menu.h"
#include "My_Sprite.h"

class Citizen
{
    public: struct tile
        {
            int type;
            int influence_point;
            int x_pos;
            int y_pos;
            int height;
            bool has_citizen;
            bool is_city;
            int citizen_id;
            int zone;
            bool passing_trought;
            enum owner{you, player2, player3};
        };
        Citizen();
        virtual ~Citizen();
        void init(RenderWindow *app_get, View *view_get);
        void draw();
        void selected();
        bool is_selected();
        void set_path(int x_path, int y_path, int path_id);
        void update();
        void on_city();
        bool is_on_city();
        bool get_goal();
        void is_over_city();
        int get_x();
        int get_previous_x();
        int get_previous_y();
        int get_y();
        void set_goal(int goal_x_get , int goal_y_get);
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
        int x, y, goal_x, goal_y, path_place, path_number;
        int path[100][2];
        tile over_tile;
        //CITIZEN INFO
        string name;
        int age;

};

#endif // CITIZEN_H
