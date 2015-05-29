#include "Sprite_Creator.h"

Sprite_Creator::Sprite_Creator()
{
    //ctor
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
void Sprite_Creator::create_character( int sunlight_get)
{
    skin.init(app, "ressources/character/base_skin.png", view1);
    eyes.init(app, "ressources/character/eyes", view1, 10 );
    hair.init(app, "ressources/character/hair", view1, 10);
    whole.init(app, "ressources/empty.png", view1);
    whole.add_sprite(&skin, sunlight_get);
    hair.set_color(color_maker(1, 1, 1, true));
    whole.add_sprite(&hair);
    eyes.set_color(color_maker(0,1, 1, true));
    whole.add_sprite(&eyes);
   // string file = whole.get_file().c_str();
    //cout<<"file"<<file<<endl;
}

Color Sprite_Creator::color_maker(int red_get, int green_get, int blue_get, bool large_randomness)
{
    int random_limit = 10;

    if(large_randomness)
    {
        random_limit = 100;
    }
    else
    {
        random_limit = 25;
    }

    srand(time(0));
    int random = 10;
    random = rand()% random_limit;
    int red = 100 * red_get + (random - random_limit);
    cout<< "rand"<< random<<endl;

    random = rand()% random_limit;
    int blue = 100 * blue_get + (random - random_limit);
    cout<< "rand"<< random<<endl;

    random = rand()% random_limit;
    int green = 100 * green_get + (random - random_limit);
    cout<< "rand"<< random<<endl;
    if(red > 255 )
    {
        red = 255;
    }
    else if(red < 0)
    {
        red = 0;
    }

    if(green > 255 )
    {
        green = 255;
    }
    else if(green < 0)
    {
        green = 0;
    }

    if(blue > 255 )
    {
        blue = 255;
    }
    else if(blue < 0)
    {
        blue = 0;
    }
    Color color1( red ,  green, blue, 255);
    return color1;
}
