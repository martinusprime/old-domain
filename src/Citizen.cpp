#include "Citizen.h"

const size_t Citizen::path_size;

Citizen::Citizen(Grid &grid, RenderWindow *app_get, View *view_get)
: m_grid(grid)
, m_move_path(path_size, std::vector<int>(2))
, m_path(path_size, std::vector<int>(2))
{
    over_city = false;
    has_goal = false;
    move_clock.restart();
    view1 = view_get;
    app = app_get;
    goal_sprite.init(app, "ressources/goal.png", view1);
    x = 0;
    y = 0;
    path_place = 0;
    path_number = 0;
    m_is_selected = false;
    sprite_creator1.init(app, view1);
    sprite.init(app,sprite_creator1.create_character(5), view1);
    name.init(app, sprite_creator1.get_character_name(), 25,  1);
}

Citizen::~Citizen()
{
    //dtor
}

int Citizen::get_x()
{
    return x;
}

int Citizen::get_y()
{
    return y;
}

bool Citizen::get_goal()
{
    return has_goal;
}

void Citizen::draw()
{
    sprite.draw( ( x - y) * 64, (y +x) * 32);
    name.draw(( x - y)  * 64, ( x + y - 1)  * 32 - 10, 10);

    if(has_goal)
    {
        goal_sprite.draw( ( m_goal_x - m_goal_y) * 50, (m_goal_x +m_goal_y) * 30);
    }
}
void Citizen::set_goal(int goal_x , int goal_y)
{
    sprite.add_color(255, 255, 255, 255);

    path_place = 0;
    m_goal_x = goal_x;
    m_goal_y = goal_y;
    has_goal = true;
    m_is_selected = false;
    find_path_to_goal();
}

void Citizen::reset_goal()
{
    for(size_t i = 0; i < m_move_path.size(); i++)
    {
        if (m_move_path[i][0] == -1 || m_move_path[i][1] == -1)
        {
            break;
        }
        m_grid(m_move_path[i][0], m_move_path[i][1]).passing_trought = false;
        m_move_path[i][0] = -1;
        m_move_path[i][1] = -1;
    }
}

void Citizen::find_path_to_goal()
{
    //a* homemade :)
    m_move_path[0][0] = get_x();
    m_move_path[0][1] = get_y();

    for(int i = 0; i<100; i++)
    {
        if( m_move_path [i][0] < m_goal_x)
        {
            m_move_path[i +1][0] = m_move_path[i][0] + 1;
        }
        else if( m_move_path [i][0] > m_goal_x)
        {
            m_move_path[i +1][0] = m_move_path[i][0] - 1;
        }
        else m_move_path[i +1][0] = m_move_path[i][0];
        if( m_move_path[i][1] < m_goal_y)
        {
            m_move_path[i +1][1] = m_move_path[i][1] + 1;
        }
        else if( m_move_path[i][1] > m_goal_y)
        {
            m_move_path[i +1][1] = m_move_path[i][1] - 1;
        }
        else m_move_path[i +1][1] = m_move_path[i][1];

        m_grid(m_move_path[i][0], m_move_path[i][1]).passing_trought = true;

        if(m_move_path[i][0] == m_goal_x && m_move_path[i][1] == m_goal_y)
        {
            for(size_t k = 0; k< m_move_path.size(); k++)
            {
                set_path( m_move_path[k][0], m_move_path[k][1], k);
                if(m_move_path[k][0] == 0 && m_move_path[k][1] == 1)
                {
                    break;
                }
            }
            break;
        }
    }
}
void Citizen::set_path(int x_path, int y_path, int path_id)
{
    m_path.at(path_id)[0] = x_path;
    m_path.at(path_id)[1] = y_path;
    path_number ++;
}

void Citizen::select()
{
    m_is_selected = true;
    sprite.add_color(90, 120, 40, 255);
}

void Citizen::deselect()
{
    m_is_selected = false;
}

void Citizen::on_city()
{
    over_city  = true;
}

bool Citizen::is_on_city()
{
    return over_city;
}

Sprite Citizen::get_sprite()
{
    return sprite.get_sprite();
}

bool Citizen::is_selected()
{
    return m_is_selected;
}
void Citizen::update()
{
    elapsed_move = move_clock.getElapsedTime();
    if(x == m_goal_x && y == m_goal_y)
    {
        path_place = 0;
        has_goal = false;
        over_city = false;
    }

    if(elapsed_move.asSeconds() >  0.5 && has_goal && m_path[path_place + 1][0] != -1)
    {
        move_clock.restart();
        path_place ++;
        x = m_path[path_place][0];
        y = m_path[path_place][1];
        cout << "move to (" << x << ", " << y << ")\n";
    }
}
