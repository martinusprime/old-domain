#ifndef GAME_MANAGER_H
#define GAME_MANAGER_H
#include <SFML/Graphics.hpp>
#include <sstream>
#include <iostream>
#include <cstdlib>
#include <memory>
#include <string>
#include <cmath>

#include "Building.h"
#include "Button.h"
#include "City.h"
#include "dialog.h"
#include "Key_event.h"
#include "Grid.h"
#include "Hud.h"
#include "Menu.h"
#include "My_Sprite.h"
#include "My_window.h"
#include "PerlinNoise.h"
#include "Sprite_Creator.h"
#include "Unit.h"
#include "Builder_gui.h"


using namespace sf;

enum Caracteristic {
    CRC_TYPE,
    CRC_ZONE,
    CRC_HEIGTH
};

enum Zoom_change { ZOOM_NO_CHANGE, ZOOM_ADD, ZOOM_LESS };

class Game_Manager
{
public:
    Game_Manager(RenderWindow *app, View &view1, int screen_x, int screen_y);
    void draw();
    void quit();
    void update();
    void show_action_button(Button &button);
    void create_city(int x, int y);
    virtual ~Game_Manager() = default;

private:
    void create_map(int map_width, int map_height);
    void draw_tile(int type, int, int);
    void draw_gui();
    int count_neighbours(unsigned int i, unsigned int j , Caracteristic typeorzoneorheight, int value, bool diagonal);
    void draw_selection();
    void draw_resources();
    void tile_description(int tile_x, int tile_y);
	void handle_mouse_click(sf::Mouse::Button click, Vector2i mouse_vec);
    void move_unit(int unit_id);
    bool handle_input_events();
    void update_units();
	void highlight_selected_tile();
    void execute_action(Action action);
    void handle_mouse_at_window_border(int x_mouse, int y_mouse);

    Key_event_handler key_event;
    RenderWindow *m_app;
    View m_view1;
    View m_view2;
    Vector2u window_vec;
    //mouse related stuff:
    Vector2f m_selection_vector;
    int m_x_cursor, m_y_cursor;

    Texture tile_texture[10];
    bool is_menu_visible;
    Menu menu1;
    Builder_gui builder_gui1;
    Clock clock_zoom;
    sf::Time zoom_time;
    bool open_window;
    int x_offset;
    int water_rate;
    int sand_rate;
    int deep_sea_rate;
    int deep_sea_expansion_rate;
    int y_offset;

    Zoom_change zoom_change;
    float zoom;
    float zoom_rate;

    static const int GRID_WIDTH = 40; //202;
    static const int GRID_HEIGHT = 40; //202;
    Grid m_grid;

    int m_w, m_h;
    int m_screen_y; //height of the game window height in pixels
    int m_screen_x; //width of the game window in pixels

    My_Sprite selection_sprite;
    My_Sprite gui_1, action_sprite;
    My_Text selection_text[5], tile_info;
    vector<My_window> windows;//1  for citizen window
    Hud interface1;
    vector<Building> m_buildings;
    int wood, iron, sand, glass, rock;
    dialog m_dialog;    
    std::vector<std::shared_ptr<Unit> > m_units;
    std::vector<City> m_cities;

};

#endif // GAME_MANAGER_H
