#include "Grid.h"

const Tile_dimension Tile::tile_size = Tile_dimension { 128, 64 };
My_Sprite Tile::influence_sprite;
My_Sprite Tile::tile_sprite[10];

void Tile::draw()
{
    Tile::tile_sprite[m_type].draw_tile( ( m_x_pos - m_y_pos) * (tile_size.x / 2), (m_y_pos + m_x_pos) * (tile_size.y / 2), random_pattern);
	/*
    if(owner == YOU)
    {
        influence_sprite.draw( ( x_pos - y_pos) * (tile_size.x / 2), (y_pos +x_pos) * (tile_size.y / 2));
    }*/
}

Grid::Grid(unsigned int width, unsigned int heigth, sf::View *view1, sf::RenderWindow *app)
    : m_grid(width, std::vector<Tile>(heigth))
    , m_view1(view1)
    , m_app(app)
	, m_resource(2)
{
             clock1.restart();

}

void Grid::loadFiles()
{
    My_Sprite resource_sprite0;
    resource_sprite0.init(m_app, "ressources/wood_ressource.png", m_view1);
    m_sprite_creator1.init(m_app, m_view1);
	m_resource[0].sprite[0].init(m_app, m_sprite_creator1.create_resources(0), m_view1, 128, 5, 1);
	m_resource[0].name = m_sprite_creator1.get_resource_name();
	m_resource[0].solidity = m_sprite_creator1.get_solidity();
	m_resource[0].flexibility = m_sprite_creator1.get_flexibility();

    //
    for (int i = 0; i <= 4; i++)
    {
        for (int j = 0; j <= 4; j++)
        {
            m_resource[1].sprite[i + 5* j].init(m_app, "ressources/resources/stone.png", m_view1, 128, 5, 1);
            m_resource[1].sprite[i+5 * j].set_text_rect(i * 128, j * 64, 128, 64);
        }
    }


    for(int i = 0; i < 10; i++)
    {
        string path = "ressources/tile" + std::to_string(i) + ".png";

        Tile::tile_sprite[i].init(m_app, path, m_view1, 128, 5 , 1);
    }
    Tile::influence_sprite.init(m_app, "ressources/player_influence.png", m_view1);
}

Tile &Grid::operator()(size_t x, size_t y)
{
    return m_grid.at(x).at(y);
}

void Grid::draw()
{
	for (size_t i = 0; i < m_grid.size(); i++)
	{
		for (size_t j = 0; j < m_grid[0].size(); j++)
		{
            if (!(*this)(i, j).passing_through)
			{
                (*this)(i, j).draw();
			}
            if ((*this)(i, j).ressource_type == RSC_WOOD  && i < 25 && j < 25)
            {
                m_resource[0].sprite[0].draw_tile((i - j)* (Tile::tile_size.x / 2), (i + j)* (Tile::tile_size.y / 2), (*this)(i, j).random_pattern);
            }	
            if ((*this)(i, j).ressource_type == RSC_STONE && i < 25 && j < 25)
            {
                m_resource[1].sprite[(*this)(i, j).resource_location].draw((i - j)* (Tile::tile_size.x / 2), (i + j)* (Tile::tile_size.y / 2));
            }
		}
	}
}
