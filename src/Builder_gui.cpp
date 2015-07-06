#include "Builder_gui.h"


Builder_gui::Builder_gui(Grid &grid, RenderWindow *app, View *view, View *view2)
    : m_grid(grid)
    , gui_sprite(app, "ressources/builder_gui.png", view2)
    , m_building(app, m_view1, 0)
    , m_cross(app, true, 0, 0, 0, view2)

{
    m_view1 = view;
    m_view2 = view2;
    m_app = app;
    buildings_name.init(m_app, "Batiments de base", 20, 0);
    m_building_button.push_back(Button{ app, m_building.get_file(), true, 0, 0, 0, 0, m_view2 });
}


Builder_gui::~Builder_gui()
{
}

void Builder_gui::draw()
{
    Vector2u windowSize = m_app->getSize();
    gui_sprite.draw(windowSize.x - gui_sprite.get_w(), 0);
    m_cross.update(windowSize.x - 128 * 4 + 50, 300);
    m_cross.draw();

    buildings_name.draw(windowSize.x - 128 * 3 + 50, 300, 20);
    m_building_button[0].update(windowSize.x - 128 * 4 + 50, 300);
    m_building_button[0].draw();
}

void Builder_gui::draw_building(int x, int y)
{
    m_building.set_coord(x, y );
    m_building.draw();
}

void Builder_gui::update()
{
   
   /* if (m_building_button[0].is_activated())
    {

    }
    */
   
}
bool Builder_gui::is_activated()
{

    if (m_cross.is_activated())
    {
        m_cross.desactivate();
        return false;
    }
    else return true;

}


bool Builder_gui::is_building_selected()
{
    if (m_building_button[0].is_activated())
    {
        m_building_button[0].desactivate();
        return true;
    }
    else return false;

}