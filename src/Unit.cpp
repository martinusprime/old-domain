#include "Unit.h"

void Unit::moveTo(int x, int y)
{
	m_x = x;
	m_y = y;
}

int Unit::get_x()
{
	return m_x;
}

int Unit::get_y()
{
	return m_y;
}