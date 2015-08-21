#pragma once
class Tile_Box
{
    struct Tile_coordinates 
    {
        int x;
        int y;
    };
public:
    Tile_Box(int top_left_tile_x, int top_left_tile_y, int right_bottom_tile_x, int right_bottom_tile_y, int grid_size_x, int grid_size_y);
    Tile_Box(int center_x, int center_y, int radius);
    virtual ~Tile_Box();
    int get_x();
    int get_y();
    void start();
    bool is_over();
private :
    Tile_coordinates m_left_top, m_right_bottom, m_center;
    int m_x, m_y, m_grid_size_x, m_grid_size_y, m_radius;
    bool m_is_over;
};

