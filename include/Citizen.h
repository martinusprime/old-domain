#pragma once

#include <SFML/Graphics.hpp>
#include <cmath>
#include <cstdlib>
#include <deque>
#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <string>


#include "Button.h"
#include "Game_Manager.h"
#include "Grid.h"
#include "Menu.h"
#include "My_Sprite.h"
#include "My_Text.h"
#include "Sprite_Creator.h"
#include "Tile.h"
#include "Unit.h"
#include "Loading_bar.h"


struct Node {
    int m_F_cost;
    int m_G_cost;
    int m_H_cost;
    Coordinate m_coord;
    Coordinate m_parent;
};

enum Work
{
    IDLE,
    HARVESTING,
    TRAVELLING,
    INFO_BUTTON,
    CONSTRUCTION_BUTTON,
    TOTEM_BUTTON,
    HARVEST_BUTTON
};

class Citizen : public Unit
{
public:
    Citizen(Grid &grid, RenderWindow *app, View *view, View *view2, Game_Manager &game_manager);
    virtual ~Citizen() = default;

    void select();
    void deselect();
    void draw() override;

    void find_path_to_goal();
    bool get_goal();
    Sprite get_sprite();
    int get_x();
    int get_y();
    std::string get_name();

    bool handle_mouse_click(Vector2f selection_vector, sf::Mouse::Button click, int x_cursor, int y_cursor) override;

    bool is_selected();
    bool is_mouse_over_actions();
    bool is_on_city();
    void is_over_city();

    void Citizen::moveTo(int x, int y);

    void on_city();


    void reset_goal();

    void set_goal(int goal_x , int goal_y);
    void set_action(Work work);
   
    void update();


    vector<Button> m_citizen_actions; //TODO make this private

private:
    void find_path_basic();
    void find_path_advanced();
    void find_path();
    std::vector<Node> get_valid_neighbours(
        const Node &node,
        const std::map<Coordinate, Node> &closed_list);
    Node get_coord_with_lowest_cost(std::map<Coordinate, Node> nodes);
    void add_to_open_list(
        Node node,
        const Coordinate &parent,
        std::map<Coordinate, Node> &open_list);

    Work m_work;

    Grid &m_grid;
    View *m_view1;
    RenderWindow *m_app;
    Event event;
    bool m_has_goal;
    bool m_is_selected;
    bool over_city;
    Clock m_move_clock;
    Sprite_Creator m_sprite_creator1;
    My_Sprite m_goal_sprite;
    My_Sprite m_sprite;
    //int m_x, m_y;
	int	m_goal_x, m_goal_y, path_place, path_number;
    /* path through which the citizen move, -1 for no path */
    std::deque<Coordinate> m_move_path;
    //CITIZEN INFO
    My_Text m_name;
    vector<My_Text> m_citizen_actions_text;
    Loading_bar m_resource_bar;
    Game_Manager &m_game_manager;
};

