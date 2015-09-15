#include "Builder_gui.h"


Builder_gui::Builder_gui(Grid &grid, RenderWindow *app, View *view, View *view2, Hud *hud)
    : m_grid(grid)
    , gui_sprite(app, "ressources/builder_gui.png", view2)
    , box_sprite(app, "ressources/color.png", view2)
    , m_cross(app, true, 0, 0, 0, view2)
    , m_hud(hud)
    , m_edit_button(app, "editer", 0, 0, 0, 0, view2)
    , m_edit_window(app, "edit", 0.5f, 0.5f, 0, 0, view2, app->getSize().x, app->getSize().y)
    , selected_building(500)
{
    m_view1 = view;
    m_view2 = view2;
    m_app = app;
    buildings_name.init(m_app, "Batiments de base", 20, 0);
    m_building.push_back(Building{ app, m_view1, 0 });
    m_building.push_back(Building{ app, m_view1, 1 });

    m_building_button.push_back(Button{ app, m_building[0].get_file(), true, 0, 0, 0, 0, m_view2 });
    m_building_button.push_back(Button{ app, m_building[1].get_file(), true, 0, 0, 0, 0, m_view2 });

    //charging the differents parts
    m_parts_button.push_back(Button{ app, "ressources/buildings/columns.png", true, 0, 0, 0, 0, m_view2 });
    m_parts_button.push_back(Button{ app, "ressources/buildings/flowers.png" , true, 0, 0, 0, 0, m_view2 });
    m_parts_button.push_back(Button{ app, "ressources/buildings/half_timber1.png", true, 0, 0, 0, 0, m_view2 });
    m_parts_button.push_back(Button{ app, "ressources/buildings/half_timber1.png", true, 0, 0, 0, 0, m_view2 });
    m_parts_button.push_back(Button{ app, "ressources/buildings/half_timber1.png", true, 0, 0, 0, 0, m_view2 });
    m_parts_button.push_back(Button{ app, "ressources/buildings/half_timber1.png", true, 0, 0, 0, 0, m_view2 });
    m_parts_button.push_back(Button{ app, "ressources/buildings/half_timber1.png", true, 0, 0, 0, 0, m_view2 });
    m_parts_button.push_back(Button{ app, "ressources/buildings/half_timber1.png", true, 0, 0, 0, 0, m_view2 });
    m_parts_button.push_back(Button{ app, "ressources/buildings/half_timber1.png", true, 0, 0, 0, 0, m_view2 });
    m_parts_button.push_back(Button{ app, "ressources/buildings/half_timber1.png", true, 0, 0, 0, 0, m_view2 });
    m_parts_button.push_back(Button{ app, "ressources/buildings/half_timber1.png", true, 0, 0, 0, 0, m_view2 });
    m_parts_button.push_back(Button{ app, "ressources/buildings/half_timber1.png", true, 0, 0, 0, 0, m_view2 });
    m_parts_button.push_back(Button{ app, "ressources/buildings/half_timber1.png", true, 0, 0, 0, 0, m_view2 });

}


Builder_gui::~Builder_gui()
{
}

void Builder_gui::draw()
{
    Vector2u windowSize = m_app->getSize();
    gui_sprite.draw(windowSize.x - gui_sprite.get_w(), 0);
    m_cross.update(windowSize.x - 128 * 4 + 50, 0);
    m_cross.draw();

    buildings_name.draw(windowSize.x - 128 * 3 + 50, 300, 20);
    m_building_button[0].update(windowSize.x - 128 * 4 + 50, 300);
    m_building_button[0].draw();

    m_building_button[1].update(windowSize.x - 128 * 4 + 50, 500);
    m_building_button[1].draw();

    if (m_building_button[0].is_activated())
    {
        m_building_button[0].desactivate();
        selected_building = 0;
    }

    if (m_building_button[1].is_activated())
    {
        m_building_button[1].desactivate();
        selected_building = 1;
    }



    m_edit_button.update(windowSize.x - 128 * 4 + 50, 200);
    if (m_edit_button.is_activated())
    {
        m_edit_button.desactivate();
        m_edit_window.activate();

    }



    if (m_edit_window.is_activated())
    {
        m_edit_window.draw();
        for (int i = 0; i < (m_parts_button.size() - 1) / 4; i++)
        {

            for (int j = 0; j < (m_parts_button.size() - 1) / 4; j++)
            {
                box_sprite.draw(20 + m_edit_window.get_x() + i * 128, 100 + m_edit_window.get_y() + j * 128);
                m_parts_button[i + j * ((m_parts_button.size() - 1) / 4)].update(20 + m_edit_window.get_x() + i * 128, 100 + m_edit_window.get_y() + j * 128);
                m_parts_button[i + j * ((m_parts_button.size() - 1) / 4)].draw();
                if (m_parts_button[i + j * ((m_parts_button.size() - 1) / 4)].is_activated())
                {
                    m_parts_button[i + j * ((m_parts_button.size() - 1) / 4)].desactivate();
                    m_building[selected_building].add_sprite(m_parts_button[i + j * ((m_parts_button.size() - 1) / 4)].get_file());
                    m_building_button[0].change_sprite(m_building[selected_building].get_file());

                }
            }
        }
    }

    m_edit_button.draw();

  
}

void Builder_gui::draw_building(int x, int y)
{
    m_building[selected_building].set_coord(x, y );
    m_building[selected_building].draw();
}

Building Builder_gui::get_building()
{
    return m_building[selected_building];
}

void Builder_gui::update()
{
   
   /* if (m_building_button[0].is_activated())
    {

    }
    */

    if (m_edit_window.is_activated())
    {
        m_edit_window.update();
    }
   
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
    if (selected_building != 500)
    { 
        return true;
    }
    else return false;

}