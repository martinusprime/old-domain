#include "Glissor.h"

Glissor::Glissor()
{
    //ctor
}

Glissor::Glissor(const Glissor &glissor_get)
{

    view1 = glissor_get.view1;
    app = glissor_get.app;
    bar = glissor_get.bar;
    cursor_bar = glissor_get.cursor_bar;
    x = glissor_get.x;
    y = glissor_get.y;
    value = glissor_get.value;
    window_x = glissor_get.window_x;
    window_y = glissor_get.window_y;
    mouse_on = glissor_get.mouse_on;
    a = glissor_get.a;
    mouse_vec = glissor_get.mouse_vec;
    rate = glissor_get.rate;
	
}
Glissor::~Glissor()
{
    //dtor
}

void Glissor::init(RenderWindow *app_get, int x_get, int y_get, int window_x_get, int window_y_get, View *view1_get)
{
    view1 = view1_get;
    window_x = window_x_get;
    window_y = window_y_get;
    x = x_get;
    y = y_get;
    app = app_get;
    bar.init(app, "ressources/bar.png", view1);
    cursor_bar.init(app, "ressources/cursor_bar.png", view1);
    rate.init(app, " 05", 55, 1);
    value = 0;
    mouse_on = false;
}

void Glissor::draw()
{
    bar.draw(x + window_x, y + window_y);
    cursor_bar.draw(x + value * 2 + window_x, y + window_y - 13);
    rate.draw(x + window_x - 75 , y + window_y , 25);

}

int Glissor::get_value()
{
   return value;

}
void Glissor::update( int x_get, int y_get)
{
    x = x_get;
    y = y_get;

    mouse_vec = Mouse::getPosition(*app);
    a = app->mapPixelToCoords(mouse_vec, *view1);
    if(Mouse::isButtonPressed(Mouse::Left) && a.x >= x +value * 2 + window_x &&  a.x <= x +value * 2 + window_x + 20
            && a.y >= y + window_y - 13 && a.y <= y + window_y - 13 + 50)
    {
        mouse_on  =true;
    }
    if(mouse_on)
    {
        int cache_value = value;
        value = (a.x - window_x- x)/2;
        if(value <=0)
        {
            value = 0;
        }
        if(value >= 100)
        {
            value = 100;
        }
        if(value != cache_value)
        {
            stringstream ss;
            ss << value;
            string str = ss.str();
            rate.refill(str);
        }
    }
    if(!Mouse::isButtonPressed(Mouse::Left))
    {
        mouse_on = false;
    }

}
