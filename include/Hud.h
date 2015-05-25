#ifndef HUD_H
#define HUD_H
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


class Hud
{
public:
    Hud();
    void init(RenderWindow *app_get, View *view_get, int screen_width_get, int screen_height_get);
    void draw();
    void draw_ressources();
    virtual ~Hud();
protected:
private:
    View *view1;
    RenderWindow *app;
    Event event;
    int screen_width, screen_height, wood_number, current_season, current_year;
    My_Sprite wood_sprite, iron_sprite, sand_sprite, glass_sprite, rock_sprite, season_sprite[4];
    My_Text wood_text, year_text;
    Clock season_clock, year_clock;
    Time season_time, year_time;


};

#endif // HUD_H
