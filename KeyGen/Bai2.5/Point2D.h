#pragma once
#include <math.h>

class Point2D
{
public:
	Point2D(char x, char y)
	{
		this->x = x;
		this->y = y;
	}
	Point2D& operator=(const Point2D& a)
	{
		this->x = a.x;
		this->y = a.y;
		return (*this);
	}
	Point2D()
	{
		this->x = 0;
		this->y = 0;
	}
	char x, y;
	float distance(Point2D inp) {
		return sqrt(
			(this->x - inp.x) * (this->x - inp.x) + (this->y - inp.y) * (this->y - inp.y)
		);
	}
};

