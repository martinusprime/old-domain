#include "Building.h"

Building::Building(RenderWindow *app, View *view, int type)
: m_sprite_creator(app, view)

{
    m_app = app;
    m_view1 = view;
    tile_x = 128;
    tile_y = 64;
    m_x = 0;
    m_y = 0;
    m_type = type;

    //if this is a field or a crop field

    if (m_type == 0)
    {

        m_sprite = My_Sprite{ app, m_sprite_creator.create_building(0), view };
    }
    else if (m_type == 1)
    {
        m_sprite= My_Sprite{ app, m_sprite_creator.create_building(1), view };
        m_sprite.set_text_rect(0, 0, 128, 64);
    }

    else
    {

        m_sprite = My_Sprite{ app, m_sprite_creator.create_building(0), view };
    }
}

void Building::draw()
{
    m_sprite.draw((m_x - m_y) * (tile_x / 2), (m_y + m_x) * (tile_y / 2));
}

void Building::add_sprite(string sprite_path)
{
    m_sprite.add_sprite(My_Sprite{ m_app, sprite_path, m_view1 }, "ressources/buildings/building1.png", 128);
}


void Building::set_coord(int x_get, int y_get)
{
    m_x = x_get;
    m_y = y_get;
}


string Building::get_file()
{
    return m_sprite.get_file();
}
