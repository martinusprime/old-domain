#include "Grid.h"

const Tile_dimension Tile::tile_size = Tile_dimension { 128, 64 };
My_Sprite Tile::influence_sprite;
My_Sprite Tile::tile_sprite[10];

void Tile::draw(int type , int x_pos, int y_pos)
{
    Tile::tile_sprite[type].draw_tile( ( x_pos - y_pos) * (tile_size.x / 2), (y_pos +x_pos) * (tile_size.y / 2), random_pattern);
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
	, m_resource(1)
{
             clock1.restart();

}

Grid::~Grid()
{
    //dtor
}

Grid::Grid(const Grid& other)
{
    //copy ctor
}

void Grid::loadFiles()
{
    My_Sprite resource_sprite0;
    m_sprite_creator1.init(m_app, m_view1);
    resource_sprite0.init(m_app, "ressources/wood_ressource.png", m_view1);
	m_resource[0].sprite.init(m_app, m_sprite_creator1.create_resources(0), m_view1, 128, 5, 1);
	m_resource[0].name = m_sprite_creator1.get_resource_name();
	m_resource[0].solidity = m_sprite_creator1.get_solidity();
	m_resource[0].flexibility = m_sprite_creator1.get_flexibility();

    for(int i = 0; i < 10; i++)
    {
        stringstream ss;
        ss << i;
        string str = ss.str();
        string path = "ressources/tile" + str + ".png";

        Tile::tile_sprite[i].init(m_app, path, m_view1, 128, 5 , 1);
    }
    Tile::influence_sprite.init(m_app, "ressources/player_influence.png", m_view1);
}

Tile &Grid::operator()(size_t x, size_t y)
{
    return m_grid[x][y];//.at(x).at(y);
}

void Grid::draw()
{
	for (size_t i = 0; i < 40; i++ ) // m_grid.size(); i++)
	{
		for (size_t j = 0; j < 40; j++)   //m_grid[0].size(); j++)   //in order to make my computer life easier for now
		{
			if (!(*this)(i, j).passing_trought)
			{
				(*this)(i, j).draw((*this)(i, j).type, (*this)(i, j).x_pos, (*this)(i, j).y_pos);
			}
			if ((*this)(i, j).ressource_type == RSC_WOOD  && i < 25 && j < 25)
			{
				m_resource[0].sprite.draw_tile(((*this)(i, j).x_pos - (*this)(i, j).y_pos)* (Tile::tile_size.x / 2), ((*this)(i, j).x_pos + (*this)(i, j).y_pos)* (Tile::tile_size.y / 2), (*this)(i, j).random_pattern);


			}
		}
	}
    // Update the window
}
