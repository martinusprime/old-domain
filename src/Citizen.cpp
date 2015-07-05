#include "Citizen.h"

#include <cstdlib>
#include <map>
#include <set>

Citizen::Citizen(Grid &grid, RenderWindow *app, View *view, View *view2, Game_Manager &game_manager)
    : m_grid(grid)
    , m_sprite_creator1(app, m_view1)
    , m_goal_sprite(app, "ressources/goal.png", m_view1)
    , m_sprite(app, m_sprite_creator1.create_character(5, GDR_WOMAN), m_view1)
    , m_game_manager(game_manager)
    , m_resource_bar(app, 0, 0, 1920, 1080, view)
{
    over_city = false;
    m_has_goal = false;
    m_move_clock.restart();
    m_view1 = view;
    m_app = app;
    m_work = IDLE;

    static int i = 0; //TODO in reality two units should never be on the same tile
    m_x = i++;
    m_y = i++;
    path_place = 0;
    path_number = 0;
    m_is_selected = false;

    m_name.init(app, m_sprite_creator1.create_character_name(GDR_WOMAN), 25,  1);


    m_citizen_actions.push_back(Button{ app, "ressources/task_observe.png", true, 0, 0, 0, 0, m_view1 });
    m_citizen_actions_text.push_back(My_Text{});
    m_citizen_actions_text[0].init(app, "observer case", 20, 1);

    m_citizen_actions.push_back(Button{ app, "ressources/task_harvest.png", true, 0, 0, 0, 0, m_view1 });
    m_citizen_actions_text.push_back(My_Text{});
    m_citizen_actions_text[1].init(app, "fonder ville", 20, 1);

    m_citizen_actions.push_back(Button{ app, "ressources/task_city.png", true, 0, 0, 0, 0, m_view1 });
    m_citizen_actions_text.push_back(My_Text{});
    m_citizen_actions_text[2].init(app, "fonder ville", 20, 1);

    m_citizen_actions.push_back(Button{ app, "ressources/task_build.png", true, 0, 0, 0, 0, m_view1 });
    m_citizen_actions_text.push_back(My_Text{});
    m_citizen_actions_text[2].init(app, "fonder ville", 20, 1);
}

int Citizen::get_x()
{
    return m_x;
}

int Citizen::get_y()
{
    return m_y;
}

std::string Citizen::get_name()
{
    return m_name.get_text();
}


bool Citizen::get_goal()
{
    return m_has_goal;
}

void Citizen::draw()
{
    m_sprite.draw((m_x - m_y) * 64 + 50, (m_y + m_x) * 32);
    m_name.draw((m_x - m_y) * 64, (m_x + m_y - 1) * 32 - 10, 10);

    if (m_has_goal)
    {
        m_goal_sprite.draw((m_goal_x - m_goal_y) * 64, (m_goal_x + m_goal_y) * 32);
    }

    if (is_selected())
    {
        if (is_on_city())
        {
        }
        if (m_work == HARVESTING)
        {
            m_resource_bar.draw();
        }
            m_citizen_actions[0].draw();
            m_citizen_actions[1].draw();
            m_citizen_actions[2].draw();
            m_citizen_actions[3].draw();
    }
}

void Citizen::set_goal(int goal_x, int goal_y)
{
    if (m_has_goal) {
        // to reset pass_through tiles
        reset_goal();
    }

    path_place = 0;
    m_goal_x = goal_x;
    m_goal_y = goal_y;
    m_has_goal = true;
    find_path_to_goal();
}

void Citizen::reset_goal()
{
    for (Coordinate coord : m_move_path)
    {
        m_grid(coord.m_x, coord.m_y).passing_through = false;
    }
    m_move_path.clear();
}

/* This does not avoid obstacles. */
void Citizen::find_path_basic()
{
    m_move_path.push_back(Coordinate{ get_x(), get_y() });
    while (1)
    {
        int next_x;
        if (m_move_path.back().m_x < m_goal_x)
        {
            next_x = m_move_path.back().m_x + 1;
        }
        else if (m_move_path.back().m_x > m_goal_x)
        {
            next_x = m_move_path.back().m_x - 1;
        }
        else next_x = m_move_path.back().m_x;

        int next_y;
        if (m_move_path.back().m_y < m_goal_y)
        {
            next_y = m_move_path.back().m_y + 1;
        }
        else if (m_move_path.back().m_y > m_goal_y)
        {
            next_y = m_move_path.back().m_y - 1;
        }
        else next_y = m_move_path.back().m_y;

        m_move_path.push_back(Coordinate{ next_x, next_y });

        m_grid(next_x, next_y).passing_through = true;

        if (next_x == m_goal_x && next_y == m_goal_y)
        {
            break;
        }
    }
}

/* Get neighbours that are walkable and not in the closed list */
std::vector<Node> Citizen::get_valid_neighbours(
        const Node &node,
        const std::map<Coordinate, Node> &closed_list)
{
    std::vector<Node> neighbours;
    for (int i = -1; i <= 1; i++) {
        for (int j = -1; j <= 1; j++) {
            if (i == 0 && j == 0) {
                continue;
            }
            int x_neighbour = node.m_coord.m_x + i;
            int y_neighbour = node.m_coord.m_y + j;
            if (!m_grid.is_valid(Coordinate{ x_neighbour, y_neighbour })) {
                continue;
            }
            if (!m_grid(x_neighbour, y_neighbour).m_is_walkable) {
                continue;
            }
            for (const auto &it : closed_list) {
                if (it.second.m_coord.m_x == x_neighbour && it.second.m_coord.m_y == y_neighbour) {
                    //this neighbour node is in the close list
                    continue;
                }
            }
            Node node;
            node.m_coord = Coordinate{ x_neighbour, y_neighbour };
            neighbours.push_back(node);
        }
    }
    return neighbours;
}

Node Citizen::get_coord_with_lowest_cost(std::map<Coordinate, Node> nodes)
{
    /* The cost is F = G + H, G is the cost of movement to this node, H is a heuristic estimating the cost from this node to the goal
       . */
    Node best;
    int best_cost = INT_MAX;
    for (const auto &it : nodes) {
        if (it.second.m_F_cost < best_cost) {
            best_cost = it.second.m_F_cost;
            best = it.second;
        }
    }
    return best;
}

void Citizen::add_to_open_list(
        Node node,
        const Coordinate &parent,
        std::map<Coordinate, Node> &open_list)
{
    //10 per move (can be changed later for roads, etc or if we want to make moving in diagonal slower than moving on the side)
    node.m_G_cost = 10;
    // we use manhattan distance as heuristic
    node.m_H_cost = std::abs(m_goal_x - node.m_coord.m_x) + std::abs(m_goal_y - node.m_coord.m_y);
    node.m_F_cost = node.m_G_cost + node.m_H_cost;
    node.m_parent = parent;

    // check if node is already in open list
    auto &it = open_list.find(node.m_coord);
    if (it != open_list.end()) {
        // if this path to that square is better (using G cost as the meature), change the parent
        // of this square
        if (it->second.m_G_cost > node.m_G_cost) {
            open_list[node.m_coord] = node;
        }
    }
    else //the node was not in the open list
    {
        open_list[node.m_coord] = node;
    }
}

/* This avoids obstacles (water, mountain, etc.) . */
void Citizen::find_path_advanced()
{
    //a* homemade :)
    
    std::map<Coordinate, Node> closed_list;
    std::map<Coordinate, Node> open_list;

    //TODO check if goal is walkable or if goal == current position

    Node start;
    start.m_coord = Coordinate{ get_x(), get_y() };
    add_to_open_list(start, start.m_coord, open_list);//parent is itself (top node of the tree)
    
    
    while (1) {
        //get node with lowest F cost from the open list
        Node best = get_coord_with_lowest_cost(open_list);

        //switch this node to the closed list (remove it from the open list)
        open_list.erase(best.m_coord);
        closed_list[best.m_coord] = best;

        //add neighbours to the open list
        Node current_node(best);
        std::vector<Node> neighbours = get_valid_neighbours(current_node, closed_list);
        for (Node node : neighbours) {
            add_to_open_list(node, current_node.m_coord, open_list);
        }
        if (best.m_coord.m_x == m_goal_x && best.m_coord.m_y == m_goal_y) {
            //we reached the goal
            break;
        }
        if (open_list.empty()) {
            //there is no possible path to our goal
            return;
        }
    }
    //go through the path starting from the goal in reverse order (using node's parents)
    Node node = closed_list[Coordinate{ m_goal_x, m_goal_y }];
    //while we didn't reach the start point (which has itself as parent)
    while (node.m_parent != node.m_coord) {
        m_move_path.push_back(node.m_coord);
        node = closed_list[node.m_parent];
    }
    //reverse vectorto have the path in the right direction
    std::reverse(m_move_path.begin(), m_move_path.end());
}

void Citizen::find_path_to_goal()
{
    //find_path_basic();
    find_path_advanced();
}

void Citizen::select()
{
    m_is_selected = true;
    m_sprite.add_color(90, 120, 40, 255);
}

bool Citizen::is_mouse_over_actions()
{
    if (m_citizen_actions[0].is_over() == true || m_citizen_actions[1].is_over() == true || m_citizen_actions[2].is_over() == true || m_citizen_actions[3].is_over() == true)
    {
        return true;
    }
    else return false;
}

void Citizen::deselect()
{
    m_is_selected = false;
    m_sprite.add_color(255, 255, 255, 255);

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
    Time elapsed_move = m_move_clock.getElapsedTime();
    if(m_has_goal && m_x == m_goal_x && m_y == m_goal_y)
    {
        path_place = 0;
        m_has_goal = false;
        over_city = false;
    }

    if(elapsed_move.asSeconds() >  0.5 && m_has_goal && !m_move_path.empty())
    {
        m_move_clock.restart();
        m_x = m_move_path[0].m_x;
        m_y = m_move_path[0].m_y;
        m_grid(m_x, m_y).passing_through = false;
        m_move_path.pop_front();
        //cout << "move to (" << x << ", " << y << ")\n";
    }


    //0->fonder une ville
    //1->rentrer dans la ville
    //2->observer la ressource
    if (is_selected())
    {
            m_citizen_actions[0].update((m_x - m_y) * 64 + 128, (m_y + m_x) * 32);
            m_citizen_actions[1].update((m_x - m_y) * 64 + 128, (m_y + m_x) * 32 + m_citizen_actions[1].get_h());
            m_citizen_actions[2].update((m_x - m_y) * 64 + 128, (m_y + m_x) * 32 + m_citizen_actions[2].get_h() * 2);
            m_citizen_actions[3].update((m_x - m_y) * 64 + 128, (m_y + m_x) * 32 + m_citizen_actions[2].get_h() * 3);
            if (m_citizen_actions[0].is_activated())
            {
                m_citizen_actions[0].desactivate();
                m_game_manager.set_info();
            }
          
            if (m_citizen_actions[1].is_activated())  //l'action sur la ressource
            {
                m_citizen_actions[1].desactivate();
                m_work = HARVESTING;
                m_resource_bar.began();
            }
            if (m_citizen_actions[2].is_activated())
            {
                m_citizen_actions[2].desactivate();
                m_game_manager.create_city(get_x(), get_y());
            }
            if (m_citizen_actions[3].is_activated())
            {
                m_citizen_actions[3].desactivate();
                m_game_manager.set_building_menu();
            }
    }
    if (m_grid(get_x(), get_y()).is_city == true)
    {
        on_city();
    }

    if (m_work == HARVESTING)
    {
        m_resource_bar.update((m_x - m_y) * 64, (m_y + m_x) * 32 - m_citizen_actions[2].get_h());

        if (m_resource_bar.get_value() >= 1.0f)
        {
            m_work = IDLE;
            if (m_grid(m_x, m_y).ressource_type == RSC_WOOD)
            {
                m_game_manager.interface1.set_resource(RSC_WOOD, 1.0f);
                m_grid(m_x, m_y).ressource_type = RSC_NO;
            }
        }
       

    }
}

bool Citizen::handle_mouse_click(Vector2f selection_vector, sf::Mouse::Button click, int x_cursor, int y_cursor)
{
    if (is_mouse_over_actions() == false)
    {
        if (get_sprite().getGlobalBounds().contains(selection_vector) && !is_selected())
        {
            if (click == sf::Mouse::Button::Left) {
                std::cout << "Unit selected" << std::endl;
                select();
            }
            else if (click == sf::Mouse::Button::Right) {
                return true; //for the  info window to open
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
    return false;

}

void Citizen::moveTo(int x, int y)
{
	m_x = x;
	m_y = y;
}