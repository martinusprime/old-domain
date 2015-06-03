#ifndef ANIMAL_H
#define ANIMAL_H
#pragma once


#include <SFML/Graphics.hpp>
#include <sstream>
#include <iostream>
#include <cstdlib>
#include <string>
#include <cmath>

#include "Grid.h"
#include "My_Sprite.h"
#include "Sprite_Creator.h"
#include "My_Text.h"


class Animal 
{
    public :
    Animal(Grid &grid, RenderWindow *app_get, View *view_get);
    virtual ~Animal();

    void select();
    void deselect();
    bool is_selected();

    void draw();
    void set_path(int x_path, int y_path, int path_id);
    void update();
    void is_over_city();
    int get_x();
    int get_y();
    Sprite get_sprite();
    void find_path_to_goal();

private:
	void find_path();

	Grid &m_grid;
	View *view1;
	RenderWindow *app;
	Event event;
	bool has_goal;
	bool m_is_selected;
	bool over_city;
	Clock move_clock;
	Time elapsed_move;
	My_Sprite sprite;
	Sprite_Creator sprite_creator1;
	/* path through which the Animal move, -1 for no path */
	vector<vector<int> > m_move_path;
	int x, y, m_goal_x, m_goal_y, path_place, path_number;
	static const size_t path_size = 150;
	vector<vector<int> > m_path;
	Tile over_tile;
	//Animal INFO
	My_Text name;
	int age;

};


