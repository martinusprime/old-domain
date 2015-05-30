#include "Sprite_Creator.h"

Sprite_Creator::Sprite_Creator()
{
flexibility = 0;
solidity = 0;
}

Sprite_Creator::~Sprite_Creator()
{
    //dtor
}
void Sprite_Creator::init(RenderWindow *app_get, View *view_get)
{
    view1 = view_get;
    app = app_get;


}
void Sprite_Creator::draw()
{
    whole.draw(250, 250);
}
string Sprite_Creator::create_character( int sunlight_get)
{
    skin.init(app, "ressources/character/base_skin.png", view1);
    eyes.init(app, "ressources/character/eyes", view1, 10 );
    hair.init(app, "ressources/character/hair", view1, 10);
    whole.init(app, "ressources/empty.png", view1);
    whole.add_sprite(&skin, sunlight_get);
    hair.set_color(color_maker(1, 1, 1, true, false));
    whole.add_sprite(&hair, "ressources/character/character0.png");
    eyes.set_color(color_maker(0,1, 1, true, true));
    whole.add_sprite(&eyes, "ressources/character/character0.png");
    string file = whole.get_file().c_str();
    return file;
}

string Sprite_Creator::create_resources( int resources_id)
{
    resources_sprite[1].init(app, "ressources/resources/tree_trunk", view1, 5);
    resources_sprite[1].set_color(color_maker(1, 0, 0, true, false));
    resources_sprite[2].init(app, "ressources/resources/tree_leaves", view1, 5);
    resources_sprite[2].set_color(color_maker(1, 1, 1, true, false));
    resources_sprite[0].init(app, "ressources/empty.png", view1);
    resources_sprite[0].add_sprite(&resources_sprite[1], "ressources/resources/tree0.png");
    resources_sprite[0].add_sprite(&resources_sprite[2], "ressources/resources/tree0.png");

    string file = resources_sprite[0].get_file().c_str();
    rand(time(0));
    flexibility =  rand%() 1 + 8;
    solidity =  rand%() 2 + 10;
    return file;
}
float Sprite_Creator::get_flexibility()
{
    return flexibility;
}
float Sprite_Creator::get_solidity()
{
    return solidity;
}

Color Sprite_Creator::color_maker(int red_get, int green_get, int blue_get, bool large_randomness, bool dark)
{
    int random_limit;
    int base_color = 100;
    if(dark)
    {
        base_color = 15;
    }
    if(large_randomness)
    {
        random_limit = 100;
    }
    else
    {
        random_limit = 25;
    }

    srand(time(0));
    int random = rand()% random_limit;
    uint8_t red = base_color * red_get + (random - random_limit);
    cout<< "rand"<< random<<endl;

    random = rand()% random_limit;
    uint8_t blue = base_color * blue_get + (random - random_limit);
    cout<< "rand"<< random<<endl;

    random = rand()% random_limit;
    uint8_t green = base_color * green_get + (random - random_limit);
    cout<< "rand"<< random<<endl;

    Color color1(red , green, blue, 255);
    return color1;
}
