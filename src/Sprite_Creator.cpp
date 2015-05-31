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
    skin.init(app, "ressources/generated/character/base_skin.png", view1);
    eyes.init(app, "ressources/generated/character/eyes", view1, 10 );
    hair.init(app, "ressources/generated/character/hair", view1, 10);
    whole.init(app, "ressources/empty.png", view1);
    whole.add_sprite(&skin, sunlight_get);
    hair.set_color(color_maker(1, 1, 1, true, false));
    whole.add_sprite(&hair, "ressources/generated/character/character01.png");
    eyes.set_color(color_maker(0 , 1, 1, false, true));
    whole.add_sprite(&eyes, "ressources/generated/character/character01.png");
    string file = whole.get_file();
    return file;
}

string Sprite_Creator::create_resources( int resources_id)
{
    whole.init(app, "ressources/empty.png", view1);
    resources_sprite[1].init(app, "ressources/generated/resources/tree_trunk", view1, 5);
    resources_sprite[1].set_color(color_maker(1, 0, 0, false, true));
    resources_sprite[2].init(app, "ressources/generated/resources/tree_leaves", view1, 5);
    resources_sprite[2].set_color(color_maker(1, 1, 1, true, false));
    whole.add_sprite(&resources_sprite[1], "ressources/generated/resources/tree0.png");
    whole.add_sprite(&resources_sprite[2], "ressources/generated/resources/tree0.png");

    srand(time(0));
    flexibility =  rand()% 1 + 8;
    solidity =  rand()% 2 + 10;


    string temp_name[3];
    int random = rand() % 5;
    ifstream name_file("ressources/resources/names.txt");

    if(name_file)
    {
        for(int i = 0; i< random; i++)
        {
            temp_name[0] = "";
            name_file >> temp_name[0];
        }

    }
    ifstream name_file2("ressources/resources/suffixes.txt");
    random = rand() % 5;
    if(name_file2)
    {
        for(int i = 0; i< random; i++)
        {
            temp_name[1] = "";
            name_file2 >> temp_name[1];
        }

    }
    ifstream name_file3("ressources/resources/adjectives.txt");
    random = rand() % 5;

    if(name_file3)
    {
        for(int i = 0; i< random; i++)
        {
            temp_name[2] = "";
            name_file3 >> temp_name[2];
        }

    }
    resource_name =  temp_name[0] +  temp_name[1] + " " + temp_name[2];
    string file = whole.get_file().c_str();
    cout<<" rseources "<< file<<endl;
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
    int red = base_color * red_get + (random - random_limit);
    cout<< "rand"<< random<<endl;

    random = rand()% random_limit;
    int blue = base_color * blue_get + (random - random_limit);
    cout<< "rand"<< random<<endl;

    random = rand()% random_limit;
    int green = base_color * green_get + (random - random_limit);
    cout<< "rand"<< random<<endl;

    if(red <0)
    {
        red = 0;
    }
    if(green < 0)
    {
        green = 0;
    }
    if(blue <0)
    {
        blue = 0;
    }

    if(red >255)
    {
        red = 255;
    }
    if(green > 255)
    {
        green = 255;
    }
    if(blue >255)
    {
        blue = 255;
    }
    Color color1(red , green, blue, 255);
    return color1;
}
