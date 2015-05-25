#ifndef MY_SPRITE_H
#define MY_SPRITE_H
#include <SFML/Graphics.hpp>
#include <iostream>
using namespace sf;

using namespace std;

class My_Sprite
{
public:
    My_Sprite();
    void draw(int x, int y);
    void init(RenderWindow *app_get, string file_get, View *view_get);
    void scale(float x_rate, float y_rate);
    void add_sprite( string file);
    void add_sprite( My_Sprite *added_sprite);
    void add_sprite( My_Sprite *added_sprite, int sunlight_get);
    void set_color(int r, int g, int b, int alpha);
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
};

#endif // MY_SPRITE_H
