#include "My_window.h"

My_window::My_window()
{
    button_number = 0;
    x = 0;
    y = 0;
    moving = false;
}

My_window::~My_window()
{
    //dtor
}

void My_window::init(RenderWindow *app_get, string name_get,  float width, float height,int x_get, int y_get, View *view1_get, int screen_x_get, int screen_y_get)
{
    x = x_get;
    y = y_get;
    view1 = view1_get;
    screen_x = screen_x_get;
    screen_y = screen_y_get;
    app = app_get;
    window_sprite.init(app, "ressources/window.png", view1);
    grip_bar.init(app, "ressources/grip_bar.png", view1);
    window_sprite.scale( width, height);
    grip_bar.scale( width, height);
    name.init(app, name_get, 55, 1);
    cross.init(app, true,  0, 0,1000 * width - 32, view1);
    activation = true;
    window_w = window_sprite.get_w();
    window_h = window_sprite.get_h();
}

void My_window::draw()
{
    window_sprite.draw(x, y);
    grip_bar.draw(x, y);
    name.draw(x+  20, y + 0, 18);
    cross.draw();
    for(Glissor &glissor : glissors)
    {
        glissor.draw();
    }
    for(int i = 0; i<button_number; i++)
    {
        button[i].draw();
    }
}

void My_window::add_glissor(int x, int y)
{
    Glissor glissor;
    glissor.init(app, x, y,100, 100 + 100 * glissors.size(), view1);
    glissors.push_back(glissor);
}

int My_window::get_glissor(int glissor_number_get)
{
    return glissors[glissor_number_get].get_value();
}

void My_window::add_button(int x, int y)
{
    button[button_number].init(app, "h", x, y, 300 , 100 * button_number , view1);
    button_number++;

}
void My_window::activate()
{
    activation =true;
}
void My_window::desactivate()
{
    activation = false;
}

void My_window::update()
{


    if(grip_bar.is_over() && Mouse::isButtonPressed(Mouse::Left) && !moving)
    {
        moving = true;
    }
    else if(!Mouse::isButtonPressed(Mouse::Left) )
    {
        moving = false;
    }
    if(moving)
    {
        Vector2i b= Mouse::getPosition(*app);
        Vector2f a = app->mapPixelToCoords(b, *view1);

        x += (a.x - mouse_save_vec.x);
        y += (a.y - mouse_save_vec.y);
        cout<<x<<endl;
        if(x > screen_x -  window_w)
        {
            x = screen_x - window_w;
        }
        if(y > screen_y - window_h)
        {
            y = screen_y - window_h;
        }
        if(x < 0)
        {
            x = 0;
        }
        if(y < 0)
        {
            y = 0;
        }
    }

    Vector2i a = Mouse::getPosition(*app);
    mouse_save_vec = app->mapPixelToCoords(a, *view1);

    for(Glissor &glissor : glissors)
    {
        glissor.update(x, y);
    }

    for(int i = 0; i < button_number; i++)
    {
        button[i].update(x, y);
    }
    cross.update(x, y);
    if(cross.is_activated())
    {
        activation = false;
    }
}

bool My_window::is_activated()
{
    return activation;
}
