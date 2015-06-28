#include "Loading_bar.h"

Loading_bar::Loading_bar(const Loading_bar &Loading_bar)
    : m_bar(Loading_bar.m_bar)
    , m_loading_bar(Loading_bar.m_loading_bar)
{
    m_view1 = Loading_bar.m_view1;
    m_app = Loading_bar.m_app;

    m_x = Loading_bar.m_x;
    m_y = Loading_bar.m_y;
    m_value = Loading_bar.m_value;
    m_window_x = Loading_bar.m_window_x;
    m_window_y = Loading_bar.m_window_y;
    m_mouse_on = Loading_bar.m_mouse_on;
    m_a = Loading_bar.m_a;
    m_mouse_vec = Loading_bar.m_mouse_vec;
    m_clock.restart();
    m_rate = Loading_bar.m_rate;
}

Loading_bar::Loading_bar(RenderWindow *app, int x, int y, int window_x, int window_y, View *view1)
    : m_bar(app, "ressources/bar.png", view1)
    , m_loading_bar(app, "ressources/bar_loading.png", view1)
{
    m_view1 = view1;
    m_window_x = window_x;
    m_window_y = window_y;
    m_x = x;
    m_y = y;
    m_app = app;
    m_rate.init(app, " 0", 55, 1);
    m_value = 0;
    m_mouse_on = false;
    m_clock.restart();
    m_loading_bar.scale(m_value, 1.0f);

}

void Loading_bar::draw()
{
    m_bar.draw(m_x , m_y  );
    m_loading_bar.draw(m_x, m_y - 13);
    if (m_mouse_on)
    {
        m_rate.draw(m_x - 75, m_y, 25);
    }
   
}

float Loading_bar::get_value()
{
    return m_value;
}

void Loading_bar::began()
{
    m_value = 0.0f;
    m_loading_bar.scale(m_value, 1.0f);
    m_clock.restart();
}

void Loading_bar::update(int x, int y)
{
    m_x = x;
    m_y = y;

    m_mouse_vec = Mouse::getPosition(*m_app);
    m_a = m_app->mapPixelToCoords(m_mouse_vec, *m_view1);
    if (Mouse::isButtonPressed(Mouse::Left) && m_a.x >= m_x + m_value * 2   &&  m_a.x <= m_x + m_value * 2   + 20
        && m_a.y >= m_y   - 13 && m_a.y <= m_y   - 13 + 50)
    {
        m_mouse_on = true;
    }
    if (m_value > 1.0f)
    {
        m_value = 1.0f;
    }

    if (m_clock.getElapsedTime().asSeconds() >= 0.05)
    {
        m_clock.restart();
        m_value += 0.05f;
        m_loading_bar.scale(m_value, 1.0f);
    }

}
