#ifndef GAME_MANAGER_H
#define GAME_MANAGER_H
#include <SFML/Graphics.hpp>
#include <sstream>
#include <iostream>
#include <cstdlib>
#include <string>
#include <cmath>

#include "Key_event.h"
#include "Grid.h"
#include "Menu.h"
#include "My_Sprite.h"
#include "My_window.h"
#include "Button.h"
#include "Citizen.h"
#include "Building.h"
#include "City.h"
#include "Sprite_Creator.h"
#include "Hud.h"

#include "PerlinNoise.h"

using namespace sf;

enum Caracteristic {
    CRC_TYPE,
    CRC_ZONE,
    CRC_HEIGTH
};




struct tile_dimension
{
    int x;
    int y;
};
enum Zoom_change { ZOOM_NO_CHANGE, ZOOM_ADD, ZOOM_LESS };

class Game_Manager
{
public:
    Game_Manager();
    void draw();
    void init(RenderWindow *app_get);
    void quit();
    void create_map(int x_beg, int y_beg);
    void update();

    virtual ~Game_Manager();
protected:
private:
    void draw_tile(int type, int, int);
    void draw_grid();
    void draw_gui();
    int count_neighbours(unsigned int i, unsigned int j , Caracteristic typeorzoneorheight, int value, bool diagonal);
    void draw_selection();
    void draw_resources();
    void tile_description(int tile_x, int tile_y);
    void mouse_selection();
    void move_unit(int unit_id);
    bool handle_key_events();
    bool is_r_click();
    bool is_l_click();
    void citizen_update();

    Key_event_handler key_event;
    RenderWindow *app;
    View view1;
    View view2;
    Vector2i mouse_vec;
    Vector2u window_vec;
    Vector2f selection_vector;
    Texture tile_texture[10];
    My_Sprite tile_sprite[10];
    bool is_menu_visible;
    int x_cursor,y_cursor;
    int iteration;
    Menu menu1;
    Clock clock_zoom;
    sf::Time zoom_time;
    bool citizen_selected, open_window;
    int x_offset;
    int map_size_x;
    int map_size_y;
    int water_rate;
    int sand_rate;
    int deep_sea_rate;
    int deep_sea_expansion_rate;
    int y_offset;
    int mouse_wheel_x;
    Zoom_change zoom_change;
    float zoom;
    float zoom_rate;
    tile_dimension tile_size;
    static const int GRID_WIDTH = 202;
    static const int GRID_HEIGTH = 202;
    Grid grid;
    /* path through which the citizen move, -1 for no path */
    vector<vector<int> > move_path;
    int w, h, city_number, citizen_number, selected_citizen;
    int screen_y;
    int screen_x;
    Citizen citizen[50];
    My_Sprite selection_sprite, influence_sprite;
    My_Sprite gui_1, action_sprite;
    My_Text selection_text[2], tile_info;
    My_window windows[8];//1  for citizen window
    Hud interface1;
    Building building[5];
    int wood, iron, sand, glass, rock;
    My_Sprite ressource_sprite[5];
    Button citizen_action[5];
    City city[5];
    Sprite_Creator sprite_created_1_test;
};

#endif // GAME_MANAGER_H
