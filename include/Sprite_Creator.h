#ifndef SPRITE_CREATOR_H
#define SPRITE_CREATOR_H
#pragma once
#include "My_Sprite.h"
#include "My_window.h"
#include <string>
#include <SFML/Graphics.hpp>

class Sprite_Creator
{
public:
    Sprite_Creator();
    void init(RenderWindow *app_get, View *view_get);
    void draw();
    string create_character( int sunlight_get);
    string create_resources( int resources_id);
    string get_file();
    string get_character_name();
    string get_resource_name();
    float get_solidity();
    float get_flexibility();
    Color color_maker(int red_get, int green_get, int blue_get, bool large_randomness, bool dark);
    virtual ~Sprite_Creator();
protected:
private:
    View *view1;
    RenderWindow *app;
    My_Sprite whole, skin, hair, eyes;
    My_Sprite resources_sprite[5];
    int sunlight;
    float solidity, flexibility;
    string resource_name, character_name;

};

#endif // SPRITE_CREATOR_H
