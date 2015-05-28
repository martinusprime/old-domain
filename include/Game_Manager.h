#ifndef GAME_MANAGER_H
#define GAME_MANAGER_H
#include <SFML/Graphics.hpp>
#include <sstream>
#include <iostream>
#include <cstdlib>
#include <string>
#include <cmath>

#include "Key_event.h"
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

class Game_Manager
{
public:
    Game_Manager();
    void draw();
    void draw_tile(int type, int, int);
    void draw_grid();
    void draw_gui();
    void init(RenderWindow *app_get);
    void quit();
    void create_map(int x_beg, int y_beg);
    void update();
    int count_neighbours(unsigned int i, unsigned int j , int typeorzoneorheight, int value, bool diagonal);
    void draw_selection();
    void draw_resources();
    void tile_description(int tile_x, int tile_y);
    void selection();
    void move_unit(int unit_id);
    bool handle_key_events();
    virtual ~Game_Manager();
protected:
private:
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
    bool is_r_click();
    int x_cursor,y_cursor;
    bool is_l_click();
    void citizen_update();
    Menu menu1;
    Clock clock_zoom;
    sf::Time zoom_time;
    bool citizen_selected, open_window;
    int screen_x, screen_y, x_offset, map_size_x,map_size_y, water_rate, sand_rate, deep_sea_rate, deep_sea_expansion_rate, y_offset, mouse_wheel_x;
    enum Zoom_change { ZOOM_NO_CHANGE, ZOOM_ADD, ZOOM_LESS };
    Zoom_change zoom_change;
    float zoom, zoom_rate;
    enum owner_enum {YOU, OTHER, OPPONENT};
    enum ressources_type_enum {no, WOOD, IRON};
    struct tile
    {
        int type;
        int x_pos;
        int y_pos;
        int height;
        bool has_citizen;
        bool is_city;
        int citizen_id;
        int zone;
        bool passing_trought;
        owner_enum owner ;
        ressources_type_enum ressource_type;

    };

    struct tile_dimension
    {
        int x;
        int y;
    };
    tile_dimension tile_size;
    tile grid[202][202];
    int path[150][2];
    int w, h, city_number, citizen_number, selected_citizen;
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
