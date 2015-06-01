#include "Grid.h"

constexpr Tile_dimension Tile::tile_size;
My_Sprite Tile::influence_sprite;
My_Sprite Tile::tile_sprite[10];

void Tile::draw(int type , int x_pos, int y_pos)
{
    Tile::tile_sprite[type].draw_tile( ( x_pos - y_pos) * (tile_size.x / 2), (y_pos +x_pos) * (tile_size.y / 2), random_pattern);

    if(owner == YOU)
    {
       // influence_sprite.draw( ( x_pos - y_pos) * (tile_size.x / 2), (y_pos +x_pos) * (tile_size.y / 2));
    }
}

Grid::Grid(unsigned int width, unsigned int heigth, sf::View *view1, sf::RenderWindow *app)
    : m_grid(width, std::vector<Tile>(heigth))
    , m_view1(view1)
    , m_app(app)
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
    m_resource_sprites.init(m_app, m_sprite_creator1.create_resources(0) , m_view1);
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
  time1 = clock1.getElapsedTime();
        if(time1.asSeconds() > 0.05)
        {
         clock1.restart();
            for(size_t i = 0; i < m_grid.size(); i++)
            {
                for(size_t j = 0; j<m_grid[0].size(); j++)
                {
                    if(!(*this)(i, j).passing_trought)
                    {
                        (*this)(i, j).draw((*this)(i, j).type, (*this)(i, j).x_pos, (*this)(i, j).y_pos );
                    }
                    if((*this)(i, j).ressource_type == RSC_WOOD  && i< 5 && j < 5)
                    {
                        m_resource_sprites.draw( ((*this)(i, j).x_pos - (*this)(i, j).y_pos)* (Tile::tile_size.x / 2), ((*this)(i, j).x_pos + (*this)(i, j).y_pos)* (Tile::tile_size.y / 2));


                    }
                }
            }
        }
    // Update the window
}
