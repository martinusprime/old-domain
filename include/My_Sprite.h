#ifndef MY_SPRITE_H
#define MY_SPRITE_H
#include <SFML/Graphics.hpp>
#include <iostream>
#include <sstream>
#include <fstream>
#include <ctime>


using namespace sf;

using namespace std;

class My_Sprite
{
public:
    My_Sprite();
    /* copy constructor */
    My_Sprite(const My_Sprite &other);
    void draw(int x, int y);
    void draw_tile(int x_get, int y_get, int random);
    void init(RenderWindow *app_get, string file_get, View *view_get);
    void init(RenderWindow *app_get, string file_get, View *view_get, int file_number);
    void init(RenderWindow *app_get, string file_get, View *view_get, int animation_width_get, int animation_length_get, float total_animation_time_get);
    void scale(float x_rate, float y_rate);
    int get_w();
    int get_h();
	void add_sprite(My_Sprite *added_sprite, string save_slot, int width);
    void add_sprite( My_Sprite *added_sprite, int sunlight_get);
    sf::Sprite get_sprite();
    void set_color(int r, int g, int b, int alpha);
    void set_color(Color color_get);
    void add_color(int r, int g, int b, int alpha);
    string get_file();
    bool is_over();
    virtual ~My_Sprite();
protected:
private:
    View *view1;
    string file;
    RenderWindow *app;
    int x, y, w, h;
    Event event;
    Texture texture;
    Sprite sprite;
    //
    int animation_width, animation_length, total_animation_time;
    Clock clock1;
    Time time1;
    IntRect animation_rect;
};

#endif // MY_SPRITE_H
