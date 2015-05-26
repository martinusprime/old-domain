#include "My_window.h"

My_window::My_window()
{
    glissor_number = 0;
    button_number = 0;
    x = 0;
    y = 0;
    moving = false;
}

My_window::~My_window()
{
    //dtor
}

void My_window::init(RenderWindow *app_get, string name_get,  float width, float height,int x_get, int y_get, View *view1_get)
{
    x = x_get;
    y = y_get;
    view1 = view1_get;
    window_x = width;
    window_y = height;
    app = app_get;
    window_sprite.init(app, "ressources/window.png", view1);
    grip_bar.init(app, "ressources/grip_bar.png", view1);
    window_sprite.scale( width, height);
    grip_bar.scale( width, height);
    name.init(app, name_get, 55, 1);
    cross.init(app, true,  0, 0,1000 * width - 32, view1);
    activation = true;
}

void My_window::draw()
{
    window_sprite.draw(x, y);
    grip_bar.draw(x, y);
    name.draw( 20, 0, 18);
    cross.draw();
    for(int i = 0; i<glissor_number; i++)
    {
        glissor[i].draw();
    }
    for(int i = 0; i<button_number; i++)
    {
        button[i].draw();
    }
}

void My_window::add_glissor(int x, int y)
{
    glissor[glissor_number].init(app, x, y,100, 100 + 100 * glissor_number, view1);
    glissor_number++;

}

void My_window::add_button(int x, int y)
{
    button[button_number].init(app, "h", x, y, 300 , 100 * glissor_number , view1);
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
    else if(!Mouse::isButtonPressed(Mouse::Left))
    {
        moving = false;
    }
    if(moving)
    {
        Vector2i b= Mouse::getPosition(*app);
        Vector2f a = app->mapPixelToCoords(b, *view1);

        x += (a.x - mouse_save_vec.x);
        y += (a.y - mouse_save_vec.y);
        if(x > 500)
        {
            x = 500;
        }
        if(y > 500)
        {
            y = 500;
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
    for(int i = 0; i < glissor_number; i++)
    {
        glissor[i].update(x, y);
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
