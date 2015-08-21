#include "Tile_Box.h"


Tile_Box::Tile_Box(int top_left_tile_x, int top_left_tile_y, int right_bottom_tile_x, int right_bottom_tile_y, int grid_size_x, int grid_size_y)
{
    m_grid_size_x = grid_size_x;
    m_grid_size_y = grid_size_y;
    m_left_top.x = top_left_tile_x;
    m_left_top.y = top_left_tile_y;
    m_right_bottom.x = right_bottom_tile_x;
    m_right_bottom.y = right_bottom_tile_y;
    m_is_over = true;
    m_radius = 0;
}

Tile_Box::Tile_Box(int center_x, int center_y, int radius)
{
    m_is_over = true;
    m_radius = radius;

    m_center.x = center_x;
    m_center.y = center_y;
}


void Tile_Box::start()
{
    m_is_over = false;
    m_x = 0;
    if (m_radius == 0)
    {
        m_y = 0;
    }
    else
    {
        m_y = - m_radius;
    }
}

bool Tile_Box::is_over()
{
    return m_is_over;
}
int Tile_Box::get_x()
{
    int ret(0);
    if (m_radius == 0)
    {

         ret = m_left_top.x + m_x;
        if (ret < m_right_bottom.x)
        {
            m_x++;
        }
        else
        {
            m_x = 0;
            m_y++;
        }

        if (ret < 0)
        {
            return 0;
        }
        else if (ret >= m_grid_size_x)
        {
            return m_grid_size_x;
        }
        else
        {
            return ret;
        }

    }
    else
    {
        if (m_y >= 0)
        {
            ret = m_center.x - (m_radius - m_y) + m_x;
        }
        else
        {
            ret = m_center.x - (m_radius + m_y) + m_x;
        }

        if (m_y >= 0)
        {
            if (ret >= m_center.x + (m_radius - m_y))
            {
                m_x = 0;
                m_y++;
            }
            else
            {
                m_x++;

            }
        }
        else
        {
            if (ret >= m_center.x + (m_radius + m_y))
            {
                m_x = 0;
                m_y++;
            }
            else
            {
                m_x++;
            }
        }

      
       
        

        return ret;
    }
}

int Tile_Box::get_y()
{
    if (m_radius == 0)
    {
        int ret = m_left_top.y + m_y;
        if (ret >= m_right_bottom.y &&  m_left_top.x + m_x >= m_right_bottom.x)
        {
            m_is_over = true;
        }
        if (ret < 0)
        {
            return 0;
        }
        else if (ret >= m_grid_size_y)
        {
            return m_grid_size_y;
        }
        else
        {
            return ret;
        }
    }
    else
    {
        int ret = m_center.y + m_y;
        
        if (ret >= m_center.y + m_radius)
        {
            m_is_over = true;
        }
        return ret;
    }
}

Tile_Box::~Tile_Box()
{
}
