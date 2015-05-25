#include "Button.h"

Button::Button()
{
}

Button::~Button()
{
    //dtor
}

void Button::init(RenderWindow *app_get, string name_get, int x_get, int y_get, int window_x_get, int window_y_get, View *view1_get)
{
    x = x_get;
    y = y_get;
    app = app_get;
    view1 = view1_get;
    window_x = window_x_get;
    window_y = window_y_get;
    button_sprite.init(app, "ressources/button.png", view1);
    float witdh_rate = name_get.size() ;
    w = witdh_rate * 20;
    button_sprite.scale( witdh_rate, 1);
    name.init(app, name_get, 55, 1);
    cross = false;
    mouse_on = false;
    mouse_click = false;
    activation = false;

}

void Button::init(RenderWindow *app_get,bool is_cross, int window_x_get, int window_y_get,int window_w_get,  View *view1_get)
{
    app = app_get;
    view1 = view1_get;
    window_x = window_w_get;
    window_y = window_y_get;
    button_sprite.init(app, "ressources/cross.png", view1);
    cross = true;
    mouse_on = false;
    mouse_click = false;
    activation = false;
}

void Button::draw()
{
    button_sprite.draw(x + window_x, y + window_y);
    if(!cross)
    {
        name.draw(x + window_x, y + window_y, 23);
    }
}

void Button::update(int x_get, int y_get)
{
    x = x_get;
    y = y_get;

    mouse_vec = Mouse::getPosition(*app);
    a = app->mapPixelToCoords(mouse_vec, *view1);
    if( a.x >= x + window_x &&  a.x <= x  + window_x + w
            && a.y >= y + window_y  && a.y <= y + window_y + 30&& cross ==false)
    {

        mouse_on  = true;
    }
    else if(a.x >= x + window_x &&  a.x <= x  + window_x + 25
            && a.y >= y + window_y  && a.y <= y + window_y + 25 && cross ==true)
    {
        mouse_on = true;
    }
    else
    {
        mouse_on = false;
        button_sprite.add_color(50, 50, 50, 255);
    }
    if(mouse_on)
    {
        button_sprite.add_color(120, 120, 120, 255);
        if(Mouse::isButtonPressed(Mouse::Left))
        {
            mouse_click = true;
        }
    }
    if(mouse_click)
    {
        button_sprite.add_color(220, 220, 220, 255);

    }
    if(!Mouse::isButtonPressed(Mouse::Left))
    {
        if(mouse_click && mouse_on)
        {
            activation = true;
        }
        mouse_click = false;

    }

}

bool Button::is_activated()
{
    return activation;
}
