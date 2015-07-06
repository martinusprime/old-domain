#include "Grid.h"


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
    resource0.m_sprites.push_back(My_Sprite{ m_app, m_sprite_creator1.create_resources(0), m_view1, Tile::TILE_WIDTH, 5, 1 });
    resource0.name = m_sprite_creator1.get_resource_name();
    resource0.solidity = m_sprite_creator1.get_solidity();
    resource0.flexibility = m_sprite_creator1.get_flexibility();
    m_resource.push_back(resource0);

    Resource resource1;
    for (int i = 0; i < 26; i++) {
        resource1.m_sprites.push_back(My_Sprite{ m_app, "ressources/resources/stone.png", m_view1, Tile::TILE_WIDTH, 5, 1 });
    }

    for (int j = 0; j < 5; j++)
    {
        for (int i = 0; i <= 4; i++)
        {
            resource1.m_sprites[i + (5 * j)].set_text_rect(i * Tile::TILE_WIDTH, j * Tile::TILE_HEIGHT, Tile::TILE_WIDTH, Tile::TILE_HEIGHT);
            cout << "i " << i << " j" << j;
        }
    }
    m_resource.push_back(resource1);


    for(int i = 0; i < 9; i++)
    {
        string path = "ressources/tile" + std::to_string(i) + ".png";

        Tile::m_tile_sprites.push_back(My_Sprite{ m_app, path, m_view1, Tile::TILE_WIDTH, 5, 1 });
    }
    Tile::m_influence_sprites.push_back(My_Sprite{ m_app, "ressources/player_influence.png", m_view1 });
    Tile::m_passing_through_sprite.reset(new My_Sprite(m_app, "ressources/", m_view1));
}

Tile &Grid::operator()(size_t x, size_t y)
{
    return m_grid.at(x).at(y);
}

Tile &Grid::operator()(Coordinate coord)
{
    return m_grid.at(coord.m_x).at(coord.m_y);
}

bool Grid::is_valid(Coordinate coord)
{
    return coord.m_x >= 0 && coord.m_x < m_grid.size() && coord.m_y >= 0 && coord.m_y < m_grid.size();
}

Resource Grid::get_ressource()
{
    return m_resource[0];
}

void Grid::draw()
{
    for (size_t i = 0; i < m_grid.size(); i++)
    {
        for (size_t j = 0; j < m_grid[0].size(); j++)
        {
            (*this)(i, j).draw();
            if ((*this)(i, j).ressource_type == RSC_WOOD )
            {
                m_resource[0].m_sprites[0].draw_tile((i - j)* (Tile::tile_size.m_w / 2), (i + j)* (Tile::tile_size.m_h / 2), (*this)(i, j).random_pattern);
            }	
            if ((*this)(i, j).ressource_type == RSC_STONE)
            {
                m_resource[1].m_sprites[(*this)(i, j).resource_location].draw((i - j)* (Tile::tile_size.m_w / 2), (i + j)* (Tile::tile_size.m_h / 2));
            }
		}
	}
    

}

void Grid::rotateRight(vector <shared_ptr<Unit>> m_units)
{
	Grid temp(m_grid[0].size(), m_grid.size(), m_view1, m_app);
	
	for (size_t i = 0; i < m_grid[0].size(); i++)
	{
		for (size_t j = 0; j < m_grid.size(); j++)
		{
			temp.m_grid[i][j] = m_grid[j][m_grid.size() - 1 - i];
			temp.m_grid[i][j].moveTo(i, j);
		}
	}
	for (size_t i = 0; i < m_units.size(); i++)
	{
		int x = m_units[i]->get_x();
		int y = m_units[i]->get_y();
		m_units[i]->moveTo(m_grid[0].size() - 1 - y, x);
	}
	for (size_t i = 0; i < m_grid[0].size(); i++)
	{
		for (size_t j = 0; j < m_grid.size(); j++)
		{
			m_grid[i][j] = temp.m_grid[i][j];
		}
	}

}

void Grid::rotateLeft(vector <shared_ptr<Unit>> m_units)
{
	Grid temp(m_grid[0].size(), m_grid.size(), m_view1, m_app);

	for (size_t i = 0; i < m_grid[0].size(); i++)
	{
		for (size_t j = 0; j < m_grid.size(); j++)
		{
			temp.m_grid[i][j] = m_grid[m_grid[0].size() - 1 - j][i];
			temp.m_grid[i][j].moveTo(i, j);
		}		
	}
	for (size_t i = 0; i < m_units.size(); i++)
	{
		int x = m_units[i]->get_x();
		int y = m_units[i]->get_y();
		m_units[i]->moveTo(y, m_grid.size() - 1 - x);
	}
	
	for (size_t i = 0; i < m_grid[0].size(); i++)
	{
		for (size_t j = 0; j < m_grid.size(); j++)
		{				
			m_grid[i][j] = temp.m_grid[i][j];
		}
	}
}