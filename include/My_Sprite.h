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
    void draw_tile(int x, int y, int random);
    void init(RenderWindow *app, string file, View *view);
    void init(RenderWindow *app, string file, View *view, int file_number);
    void init(RenderWindow *app, string file, View *view, int animation_width, int animation_length, float total_animation_time);
    void scale(float x_rate, float y_rate);
    int get_w();
    int get_h();
	void add_sprite(My_Sprite *added_sprite, string save_slot, int width);
    void add_sprite( My_Sprite *added_sprite, int sunlight);
    sf::Sprite get_sprite();
    void set_color(int r, int g, int b, int alpha);
    void set_color(Color color_get);
    void add_color(int r, int g, int b, int alpha);
    string get_file();
    bool is_over();
    virtual ~My_Sprite() = default;
protected:
private:
    View *m_view1;
    string m_file;
    RenderWindow *m_app;
    int m_x, m_y, m_w, m_h;
    Event m_event;
    Texture m_texture;
    Sprite m_sprite;

    int m_animation_width, m_animation_length, m_total_animation_time;
    Clock m_clock1;
    Time m_time1;
    IntRect m_animation_rect;
};

#endif // MY_SPRITE_H
