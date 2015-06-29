
#pragma once

#include <SFML/Graphics.hpp>
#include <string>

/* Model a unit (citizen, soldier, ...) */
class Unit {
public:
    virtual void draw() = 0; //TODO move to My_Drawable and make Unit inherit from My_Drawable
    virtual void update() = 0;
    virtual bool handle_mouse_click(sf::Vector2f selection_vector, sf::Mouse::Button click, int x_cursor, int y_cursor) = 0;
    virtual bool is_mouse_over_actions() = 0;
    virtual bool is_selected() = 0;

	void moveTo(int x, int y);
	int get_x();
	int get_y();

	int m_x, m_y;
};