#include "City.h"

City::City(RenderWindow *app, View *view, int x, int y, int tile_size_x, int tile_size_y)
: m_sprite(app, "ressources/buildings/totem_pillar.png", m_view1)

{
    m_app = app;
    m_view1 = view;
    m_tile_size_x = tile_size_x;
    m_tile_size_y = tile_size_y;
    
    m_x = x;
    m_y = y;

}

void City::draw()
{
    m_sprite.draw(( m_x - m_y) * (m_tile_size_x / 2), (m_x + m_y - 2) * (m_tile_size_y / 2));
    //m_name.draw(( m_x - m_y)  * (m_tile_size_x / 2), ( m_x + m_y - 2)  * (m_tile_size_y / 2) - 10, 10);
}

void City::create_city()
{
    //don't know why but this text make all others my_text crazy !

   // m_name.init(m_app, "rien", 12, 1);
}
