#include "dialog.h"

dialog::dialog(Grid &grid, RenderWindow *app, View *view)
{
    m_window.init(app, "dialogue", 0.2, 0.2, 0, 0, view, 100, 280);
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