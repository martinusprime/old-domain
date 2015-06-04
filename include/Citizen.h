#pragma once

#include <SFML/Graphics.hpp>
#include <sstream>
#include <iostream>
#include <cstdlib>
#include <string>
#include <cmath>

#include "Button.h"
#include "Game_Manager.h"
#include "Grid.h"
#include "Menu.h"
#include "My_Sprite.h"
#include "My_Text.h"
#include "Sprite_Creator.h"
#include "Unit.h"

class Citizen : public Unit
{
public:
    Citizen(Grid &grid, RenderWindow *app, View *view, View *view2, Game_Manager &game_manager);
    virtual ~Citizen() = default;

    void select();
    void deselect();
    bool is_selected();

    void on_city();
    bool is_on_city();

    bool get_goal();
    void set_goal(int goal_x , int goal_y);
    void reset_goal();

    void draw() override;
    void set_path(int x_path, int y_path, int path_id);
    void update();
    void is_over_city();
    int get_x();
    int get_y();
    Sprite get_sprite();
    void find_path_to_goal();
    void handle_mouse_click(Vector2f selection_vector, sf::Mouse::Button click, int x_cursor, int y_cursor) override;
    vector<Button> m_citizen_actions; //TODO make this private

private:
    void find_path();
    Grid &m_grid;
    View *m_view1;
    RenderWindow *m_app;
    Event event;
    bool has_goal;
    bool m_is_selected;
    bool over_city;
    Clock move_clock;
    Time elapsed_move;
    Sprite_Creator m_sprite_creator1;
    My_Sprite m_goal_sprite;
    My_Sprite m_sprite;
    /* path through which the citizen move, -1 for no path */
    vector<vector<int> > m_move_path;
    int x, y, m_goal_x, m_goal_y, path_place, path_number;
    static const size_t path_size = 150;
    vector<vector<int> > m_path;
    Tile over_tile;
    //CITIZEN INFO
    My_Text m_name;
    int m_age;
    Game_Manager &m_game_manager;
};

