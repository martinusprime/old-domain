#include "Citizen.h"

Citizen::Citizen()
{
    over_city = false;
    is_goal = false;
}

Citizen::~Citizen()
{
    //dtor
}

void Citizen::init(RenderWindow *app_get, View *view_get)
{
    move_clock.restart();
    view1 = view_get;
    app = app_get;
    goal_sprite.init(app, "ressources/goal.png", view1);
    x = 0;
    y = 0;
    path_place = 0;
    path_number = 0;
    selection = false;
    //sprite_creator1->init(app, view1);
        sprite.init(app,"ressources/character/character01.png" , view1);
    //sprite_creator1->color_maker( 1, 1, 1, true);
}
int Citizen::get_x()
{
    return x;
}

int Citizen::get_y()
{
    return y;
}
int Citizen::get_previous_x()
{
    return path[path_place - 1][0];
}
int Citizen::get_previous_y()
{
    return path[path_place - 1][1];
}
bool Citizen::get_goal()
{
    return is_goal;
}

void Citizen::draw()
{


    sprite.draw( ( x - y) * 50, (y +x) * 30);
    if(is_goal)
    {
        goal_sprite.draw( ( goal_x - goal_y) * 50, (goal_x +goal_y) * 30);
    }
}
void Citizen::set_goal(int goal_x_get , int goal_y_get)
{
    sprite.add_color(255, 255, 255, 255);

    path_place = 0;
    goal_x = goal_x_get;
    goal_y = goal_y_get;
    is_goal = true;
    selection = false;

}
void Citizen::set_path(int x_path, int y_path, int path_id)
{

    path[path_id][0] = x_path;
    path[path_id][1] = y_path;
    path_number ++;

}
void Citizen::selected()
{
    selection = true;
    sprite.add_color(90, 120, 40, 255);
}

void Citizen::on_city()
{
    over_city  = true;
}

bool Citizen::is_on_city()
{
    return over_city;
}

bool Citizen::is_selected()
{
    return selection;
}
void Citizen::update()
{
    elapsed_move = move_clock.getElapsedTime();
    if(x == goal_x && y == goal_y)
    {
        path_place = 0;
        is_goal = false;
        over_city = false;
    }

    if(elapsed_move.asSeconds() >  1.0 && is_goal && path[path_place + 1][0] != -1)

    {
        move_clock.restart();
        path_place ++;
        x = path[path_place][0];
        y = path[path_place][1];

    }
}
