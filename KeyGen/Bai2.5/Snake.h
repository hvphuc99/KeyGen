#pragma once
#include <vector>
#include "Matrix.h"

class Point2D;
class Matrix;

class Snake
{
public:
	Snake(Matrix* matrix);

	Point2D getCurrentPosition();
	bool isMovable(char x, char y, state current_destination);

	bool hasArrived(char x, char y, state current_destination);

	void move(char x, char y);

	void unmove(char x, char y);
private:
	std::vector<Point2D> position;
	Matrix* matrix;
	Point2D last_move;
};


