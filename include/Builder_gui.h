#pragma once

#include <SFML/Graphics.hpp>
#include <sstream>
#include <iostream>
#include <cstdlib>
#include <string>
#include <cmath>

#include "Building.h"
#include "Button.h"
#include "Grid.h"
#include "Hud.h"
#include "My_Sprite.h"
#include "My_Text.h"

class Builder_gui
{
public:
    Builder_gui( Grid &grid, RenderWindow *app, View *view, View *view2, Hud *hud);
    ~Builder_gui();
    void draw();
    void draw_building(int x, int y);
    Building get_building();

    bool is_activated();
    bool is_building_selected();
    void update();

private : 
    Hud * m_hud;
    Grid &m_grid;
    View *m_view1, *m_view2;
    RenderWindow *m_app;
    Event event;
    My_Sprite gui_sprite, box_sprite;
    std::vector <Button> m_parts_button;
    std::vector <Button> m_building_button;
    Button m_cross;
    vector<Building> m_building;
    My_Text buildings_name;
    Button m_edit_button;
    My_window m_edit_window;
    int selected_building;

};

