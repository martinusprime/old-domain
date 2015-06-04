#include "Grid.h"

const Tile_dimension Tile::tile_size = Tile_dimension { 128, 64 };
vector<My_Sprite> Tile::influence_sprites;
vector<My_Sprite> Tile::tile_sprites;


void Tile::draw()
{
    Tile::tile_sprites[m_type].draw_tile( ( m_x_pos - m_y_pos) * (tile_size.x / 2), (m_y_pos + m_x_pos) * (tile_size.y / 2), random_pattern);
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
    , m_sprite_creator1(m_app, m_view1)

{
    clock1.restart();
}

void Grid::loadFiles()
{

    My_Sprite resource_sprite0(m_app, "ressources/wood_ressource.png", m_view1);
    
    Resource resource0;
    resource0.sprite[0] = My_Sprite{ m_app, m_sprite_creator1.create_resources(0), m_view1, 128, 5, 1 };
    resource0.name = m_sprite_creator1.get_resource_name();
    resource0.solidity = m_sprite_creator1.get_solidity();
    resource0.flexibility = m_sprite_creator1.get_flexibility();
    m_resource.push_back(resource0);

    Resource resource1;
    for (int i = 0; i <= 4; i++)
    {
        for (int j = 0; j <= 4; j++)
        {
            resource1.sprite[i + 5 * j] =My_Sprite{ m_app, "ressources/resources/stone.png", m_view1, 128, 5, 1 };
            resource1.sprite[i+5 * j].set_text_rect(i * 128, j * 64, 128, 64);
        }
    }
    m_resource.push_back(resource1);


    for(int i = 0; i < 10; i++)
    {
        string path = "ressources/tile" + std::to_string(i) + ".png";

        Tile::tile_sprites.push_back(My_Sprite{ m_app, path, m_view1, 128, 5, 1 });
    }
    Tile::influence_sprites.push_back(My_Sprite{ m_app, "ressources/player_influence.png", m_view1 });
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
