#include "dialog.h"

dialog::dialog(Grid &grid, RenderWindow *app, View *view, int screen_x, int screen_y)
    : m_window(app, "dialogue", 0.2, 0.2, 0, 0, view, screen_x, screen_y)
{

}

dialog::~dialog()
{
    //dtor
}

void dialog::draw()
{
    m_window.draw();
    m_window.update();
}