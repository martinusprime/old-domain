#include "Random.h"
#include "Sprite_Creator.h"

Sprite_Creator::Sprite_Creator(RenderWindow *app, View *view)
{
    sunlight = 0;
    flexibility = 0.0f;
    solidity = 0;
    m_view1 = view;
    m_app = app;
}

/*void Sprite_Creator::draw()
{
    whole.draw(250, 250);
}*/
string Sprite_Creator::create_character_name(Gender gender)
{
    string character_name;

    string temp_name[3];
    int random = Random::get_int(0, 6);
    if (gender == GDR_WOMAN)
    {
        ifstream name_file("ressources/character/namesf.txt");

        if (name_file)
        {
            for (int i = 0; i <= random; i++)
            {
                temp_name[0] = "";
                name_file >> temp_name[0];
            }
        }
    }
    else
    {
        ifstream name_file("ressources/character/names.txt");

        if (name_file)
        {
            for (int i = 0; i <= random; i++)
            {
                temp_name[0] = "";
                name_file >> temp_name[0];
            }
        }
    }


    ifstream name_file2("ressources/character/suffixes.txt");

    if (name_file2) {
        random = Random::get_int(0, 6);
        for (int i = 0; i < random; i++)
        {
            temp_name[1] = "";
            name_file2 >> temp_name[1];
        }
    }

    ifstream name_file3("ressources/character/last_names.txt");
    if (name_file3) {
        random = Random::get_int(0, 6);
        for (int i = 0; i < random; i++)
        {
            temp_name[2] = "";
            name_file3 >> temp_name[2];
        }
    }

    character_name = temp_name[0] + temp_name[1] + std::string(" ") + temp_name[2];
    return character_name;
}

string Sprite_Creator::get_resource_name()
{
        return resource_name;
}

string Sprite_Creator::create_character( int sunlight_get, Gender gender)
{
    My_Sprite whole(m_app, "ressources/empty.png", m_view1);;
    if (gender == GDR_WOMAN)
    {
        My_Sprite skin(m_app, "ressources/generated/character/base_skinf.png", m_view1);
        My_Sprite eyes(m_app, "ressources/generated/character/eyes", m_view1, 10);
        My_Sprite hair(m_app, "ressources/generated/character/hairf", m_view1, 10);
        whole.add_sprite(skin, sunlight_get);
        hair.set_color(color_maker(1.5, 1, 1.5, true, false));
        whole.add_sprite(hair, "ressources/generated/character/character01.png", 128);
        eyes.set_color(color_maker(0, 1, 1, false, true));
        whole.add_sprite(eyes, "ressources/generated/character/character01.png", 128);
    }
    else
    {
        My_Sprite skin(m_app, "ressources/generated/character/base_skin.png", m_view1);
        My_Sprite eyes(m_app, "ressources/generated/character/eyes", m_view1, 10);
        My_Sprite hair(m_app, "ressources/generated/character/hair", m_view1, 10);
        whole.add_sprite(skin, sunlight_get);
        hair.set_color(color_maker(1, 1, 1, true, false));
        whole.add_sprite(hair, "ressources/generated/character/character01.png", 128);
        eyes.set_color(color_maker(0, 1, 1, false, true));
        whole.add_sprite(eyes, "ressources/generated/character/character01.png", 128);
    }
    My_Sprite skin(m_app, "ressources/generated/character/base_skin.png", m_view1);
       
    string file = whole.get_file();
    return file;
}

string Sprite_Creator::create_resources( int resources_id)
{
    is_fruit = Random::get_int(0, 1);

    My_Sprite whole(m_app, "ressources/empty_tile.png", m_view1);

    resources_sprites.push_back(My_Sprite{ m_app, "ressources/generated/resources/tree_trunk", m_view1, 5 });
    resources_sprites[0].set_color(color_maker(1, 0, 0, false, true));

    resources_sprites.push_back(My_Sprite{ m_app, "ressources/generated/resources/tree_leaves", m_view1, 5 });
    resources_sprites[1].set_color(color_maker(1, 1, .5, true, false));
    if (is_fruit)
    {
        resources_sprites.push_back(My_Sprite{ m_app, "ressources/generated/resources/fruit", m_view1, 5 });
        resources_sprites[2].set_color(color_maker(1.8, 0.4, 1.6, true, false));
    }
    whole.add_sprite(resources_sprites[0], "ressources/generated/resources/tree0.png", 640);
    whole.add_sprite(resources_sprites[1], "ressources/generated/resources/tree0.png", 640);
    if (is_fruit)
    {
        whole.add_sprite(resources_sprites[2], "ressources/generated/resources/tree0.png", 640);
    }
    flexibility =  Random::get_float(1, 9);
    solidity = Random::get_float(1, 11);

    string temp_name[3];

    ifstream name_file("ressources/resources/names.txt");
    for (int i = 0; i < Random::get_int(1, 6); i++)
    {
        temp_name[0] = "";
        name_file >> temp_name[0];
    }


    ifstream name_file2("ressources/resources/suffixes.txt");
    for (int i = 0; i < Random::get_int(1, 6); i++)
    {
        temp_name[1] = "";
        name_file2 >> temp_name[1];
    }

    ifstream name_file3("ressources/resources/adjectives.txt");
    for (int i = 0; i < Random::get_int(1, 6); i++)
    {
        temp_name[2] = "";
        name_file3 >> temp_name[2];
    }

    resource_name =  temp_name[0] +  temp_name[1] + " " + temp_name[2];
    string file = whole.get_file();
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

Color Sprite_Creator::color_maker(float red_get, float green_get, float blue_get, bool large_randomness, bool dark)
{
    int random_limit;
    int base_color = 50;
    if(dark)
    {
        base_color = 15;
    }
    if(large_randomness)
    {
        random_limit = 150;
    }
    else
    {
        random_limit = 40;
    }

    int random = Random::get_int(40, random_limit);
    int red = (base_color * red_get )+ random ;
 //   cout<< "rand"<< random<<endl;

    random = Random::get_int(0, random_limit);
    int blue = (base_color * blue_get )+ random ;
 //   cout<< "rand"<< random<<endl;

    random = Random::get_int(0, random_limit);
    int green = (base_color * green_get )+ random ;
 //   cout<< "rand"<< random<<endl;

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
