#include "Citizen.h"

const size_t Citizen::path_size;

Citizen::Citizen(Grid &grid, RenderWindow *app, View *view, View *view2, Game_Manager &game_manager)
: m_grid(grid)
, m_sprite_creator1(app, m_view1)
, m_goal_sprite(app, "ressources/goal.png", m_view1)
, m_sprite(app, m_sprite_creator1.create_character(5), m_view1)
, m_move_path(path_size, std::vector<int>(2))
, m_path(path_size, std::vector<int>(2))
, m_game_manager(game_manager)
{
    over_city = false;
    has_goal = false;
    move_clock.restart();
    m_view1 = view;
    m_app = app;

    x = 0;
    y = 0;
    path_place = 0;
    path_number = 0;
    m_is_selected = false;

    m_name.init(app, m_sprite_creator1.get_character_name(), 25,  1);

    m_citizen_actions.push_back(Button{ app, "Fonder une ville", 0, 0, 0, 0, view2 });
    m_citizen_actions.push_back(Button{ app, "Rentrer dans la ville", 0, 0, 0, 0, view2 });
    m_citizen_actions.push_back(Button{ app, "Observer la ressource", 0, 0, 0, 0, view2 });
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
    m_sprite.draw( ( x - y) * 64 + 50, (y +x) * 32 );
    m_name.draw(( x - y)  * 64, ( x + y - 1)  * 32 - 10, 10);

    if(has_goal)
    {
        m_goal_sprite.draw( ( m_goal_x - m_goal_y) * 64, (m_goal_x +m_goal_y) * 32);
    }

    if (is_selected())
    {
        m_citizen_actions[0].draw();
        if (is_on_city())
        {
            m_citizen_actions[1].draw();
        }
        else
        {
            m_citizen_actions[2].draw();
        }
    }
}

void Citizen::set_goal(int goal_x , int goal_y)
{
    if (has_goal) {
        //also to reset pass_through tiles
        reset_goal();
    }
    m_sprite.add_color(255, 255, 255, 255);

    path_place = 0;
    m_goal_x = goal_x;
    m_goal_y = goal_y;
    has_goal = true;
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
        m_grid(m_move_path[i][0], m_move_path[i][1]).passing_through = false;
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

        if (i != 0)
        {
            m_grid(m_move_path[i][0], m_move_path[i][1]).passing_through = true;
        }

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
    m_sprite.add_color(90, 120, 40, 255);
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
    return m_sprite.get_sprite();
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
        m_grid(x, y).passing_through = false;
        //cout << "move to (" << x << ", " << y << ")\n";
    }


    //0->fonder une ville
    //1->rentrer dans la ville
    //2->observer la ressource
    if (is_selected())
    {
        m_game_manager.show_action_button(m_citizen_actions[0]);
    }

    if (m_citizen_actions[0].is_activated())
    {
        m_game_manager.create_city(get_x(), get_y());

    }
    if (m_citizen_actions[2].is_activated())  //l'action sur la ressource
    {
        //TODO
        //m_cities.push_back(City{ m_app, &m_view1, m_units[0]->get_x(), m_units[0]->get_y(), Tile::tile_size.x, Tile::tile_size.y });
        // windows[1].init(app, "Action", 550, 400, w/2, h/2, &view1);

        //m_grid(get_x(), get_x()).is_city = true;
    }
    if (m_grid(get_x(), get_y()).is_city == true)
    {
        on_city();
    }
}

void Citizen::handle_mouse_click(Vector2f selection_vector, sf::Mouse::Button click, int x_cursor, int y_cursor)
{
    if (get_sprite().getGlobalBounds().contains(selection_vector) && !is_selected())
    {
        if (click == sf::Mouse::Button::Left) {
            std::cout << "Unit selected" << std::endl;
            select();
        }
        else if (click == sf::Mouse::Button::Right) {
            // ??
        }
    }
    if (is_selected() && (x_cursor != get_x() || y_cursor != get_y()))
    {
        if (click == sf::Mouse::Button::Right) {
            set_goal(x_cursor, y_cursor);
        }
        else if (click == sf::Mouse::Button::Left) {
            deselect();
        }
    }
}
