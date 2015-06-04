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
    Hud(RenderWindow *app, View *view, int screen_width, int screen_height);
    void draw();
    void draw_ressources();
    virtual ~Hud() = default;

private:
    View *m_view1;
    RenderWindow *m_app;
    Event event;
    int m_screen_width, m_screen_height;
    int wood_number, current_season, current_year, year_lenght;
    My_Sprite wood_sprite, iron_sprite, sand_sprite, glass_sprite, rock_sprite;
    vector<My_Sprite> season_sprites;
    My_Text wood_text, year_text;
    Clock season_clock, year_clock;
    Time season_time, year_time;
};

