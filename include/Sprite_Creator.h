#pragma once

#include "My_Sprite.h"
#include "My_window.h"
#include <string>
#include <SFML/Graphics.hpp>

enum Gender {
    GDR_WOMAN,
    GDR_MAN
};

class Sprite_Creator
{
public:
    Sprite_Creator(RenderWindow *app, View *view);
    /*void draw();*/
    string create_character(int sunlight_get, Gender gender);
    string create_resources(int resources_id);
    string create_building(int building_type);
    string get_file();
    static string create_character_name(Gender gender);
    string get_resource_name();
    float get_solidity();
    float get_flexibility();
    Color color_maker(float red_get, float green_get, float blue_get, bool large_randomness, bool dark);
    virtual ~Sprite_Creator() = default;

private:
    View *m_view1;
    RenderWindow *m_app;
    std::vector<My_Sprite> resources_sprites;
    int sunlight;
    float solidity, flexibility;
    bool is_fruit;
    string resource_name;
};


