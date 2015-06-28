#pragma once

#include <SFML/Graphics.hpp>
#include <sstream>
#include <iostream>
#include <cstdlib>
#include <string>
#include <cmath>
#include "Grid.h"
#include "Info.h"
#include "Menu.h"
#include "My_Sprite.h"
#include "My_Text.h"
#include "Tile.h"

class Hud
{
public:
    Hud(RenderWindow *app, Grid &grid, View *view, int screen_width, int screen_height);
    void draw();
    void draw_ressources();
    void set_resource(Ressources_type_enum resource_type, float number);
    virtual ~Hud() = default;

private:
    View *m_view1;
    RenderWindow *m_app;
    Event event;
    Grid &m_grid;
    int m_screen_width, m_screen_height;
    int current_season, current_year, year_lenght;
    float wood_number;
    My_Sprite wood_sprite, iron_sprite, sand_sprite, glass_sprite, rock_sprite;
    vector<My_Sprite> season_sprites;
    vector<Button> tasks_sprites;
    My_Sprite task_box;
    My_Text wood_text, year_text;
    Clock season_clock, year_clock;
    Time season_time, year_time;

    My_window m_resources_window;
};

