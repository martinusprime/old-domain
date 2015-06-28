#include "My_window.h"

My_window::My_window(RenderWindow *app, string name,  float width, float height, int x, int y, View *view1, int screen_x, int screen_y)
: window_sprite(app, "ressources/window.png", view1)
, grip_bar(app, "ressources/grip_bar.png", view1)
, m_cross(app, true, 0, 0, 1000 * width - 32, view1)
{
    moving = false;
    is_text = false;
    is_image = false;
    m_x = x;
    m_y = y;
    m_view1 = view1;
    m_screen_x = screen_x;
    m_screen_y = screen_y;
    m_app = app;
    window_sprite.scale( width, height);
    grip_bar.scale( width, height);
    m_name.init(app, name, 55, 1);
    activation = true;
    window_w = window_sprite.get_w();
    window_h = window_sprite.get_h();
}

void My_window::draw()
{
    window_sprite.draw(m_x, m_y);
    grip_bar.draw(m_x, m_y);
    m_name.draw(m_x+  20, m_y + 0, 18);
    m_cross.draw();
    for(Glissor &glissor : glissors)
    {
        glissor.draw();
    }
    for(Button &button : m_buttons)
    {
        button.draw();
    }
   
    if (is_text)
    {
        for (int i = 0; i <m_texts.size() ; i++)
        {
            m_texts[i].draw(m_x + m_text_x[i], m_y + m_text_y[i], 20);
        }

    }
    if (is_image)
    {
        for (int i = 0; i <sprites.size(); i++)
        {
            sprites[i].draw(m_x + m_image_x[i], m_y + m_image_y[i]);
        }

    }
}

void My_window::add_glissor(int x, int y)
{
    Glissor glissor(m_app, x, y,100, 100 + 100 * glissors.size(), m_view1);
    glissors.push_back(glissor);
}

void My_window::refill_text(int text_number, string content)
{
    m_texts[text_number].refill(content);
}

void My_window::add_image(int x, int y, string path)
{
    My_Sprite sprite1(m_app, path, m_view1);
    sprites.push_back(sprite1);
    is_image = true;
    m_image_x.push_back(x);
    m_image_y.push_back(y);
}

int My_window::get_glissor(int glissor_number_get)
{
    return glissors[glissor_number_get].get_value();
}

void My_window::add_button(int x, int y)
{
    m_buttons.push_back(Button{ m_app, "h", x, y, 300, static_cast<int>(100 * m_buttons.size() - 1), m_view1 });
}

void My_window::add_text(int x, int y, string content)
{
    m_texts.push_back(My_Text{});
    m_texts[m_texts.size() - 1].init( m_app, content, 20, 1);
    is_text = true;
    m_text_x.push_back(x);
    m_text_y.push_back(y);

}


void My_window::activate()
{
    moving = false;
    m_cross.desactivate();
    activation = true;
}

void My_window::desactivate()
{
    activation = false;
}

void My_window::set_name(string name)
{
    m_name.refill(name);
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
        Vector2i b= Mouse::getPosition(*m_app);
        Vector2f a = m_app->mapPixelToCoords(b, *m_view1);

        m_x += (a.x - mouse_save_vec.x);
        m_y += (a.y - mouse_save_vec.y);
        cout<<m_x<<endl;
        if(m_x > m_screen_x -  window_w)
        {
            m_x = m_screen_x - window_w;
        }
        if(m_y > m_screen_y - window_h)
        {
            m_y = m_screen_y - window_h;
        }
        if(m_x < 0)
        {
            m_x = 0;
        }
        if(m_y < 0)
        {
            m_y = 0;
        }
    }

    Vector2i a = Mouse::getPosition(*m_app);
    mouse_save_vec = m_app->mapPixelToCoords(a, *m_view1);

    for(Glissor &glissor : glissors)
    {
        glissor.update(m_x, m_y);
    }

    for(Button &button : m_buttons)
    {
        button.update(m_x, m_y);
    }

    m_cross.update((m_x + window_w) - 50  , m_y);

    if(m_cross.is_activated())
    {
        activation = false;
    }
}

bool My_window::is_activated()
{
    return activation;
}
