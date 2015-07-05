#include "Building.h"

Building::Building(RenderWindow *app, View *view, int type)
: m_sprite_creator(app, view)
, m_sprite(app, m_sprite_creator.create_building(0), view)

{
    m_app = app;
    m_view1 = view;

    m_x = 0;
    m_y = 0;
    m_type = type;
    My_Sprite door(m_app, "ressources/buildings/columns.png", m_view1);
    m_sprite.add_sprite(door, "ressources/buildings/building1.png", 128);


}

void Building::draw(int x_get, int y_get)
{
    m_sprite.draw(x_get, y_get);
}


string Building::get_file()
{
    return m_sprite.get_file();
}
