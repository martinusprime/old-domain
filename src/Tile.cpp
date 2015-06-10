#include "Tile.h"

const Tile_dimension Tile::tile_size = Tile_dimension{ Tile::TILE_WIDTH, Tile::TILE_HEIGHT };
vector<My_Sprite> Tile::m_influence_sprites;
vector<My_Sprite> Tile::m_tile_sprites;
const int Tile::TILE_HEIGHT;
const int Tile::TILE_WIDTH;
shared_ptr<My_Sprite> Tile::m_passing_through_sprite;

Tile::Tile()
    : m_type(0)
    , random_pattern(0)
    , resource_location(0)
    , influence_point(0)
    , m_x_pos(0)
    , m_y_pos(0)
    , height(0)
    , is_city(false)
    , m_is_walkable(true)
    , citizen_id(0)
    , zone(true)
    , passing_through(false)
    , owner(NOBODY) 
{

}

void Tile::draw()
{
    if (passing_through)
    {

        return;
    }
    Tile::m_tile_sprites[m_type].draw_tile((m_x_pos - m_y_pos) * (tile_size.m_w / 2), (m_y_pos + m_x_pos) * (tile_size.m_h / 2), random_pattern);
    /*
    if(owner == YOU)
    {
    influence_sprite.draw( ( x_pos - y_pos) * (tile_size.x / 2), (y_pos +x_pos) * (tile_size.y / 2));
    }*/
}

void Tile::moveTo(int x, int y)
{
	m_x_pos = x;
	m_y_pos = y;
}