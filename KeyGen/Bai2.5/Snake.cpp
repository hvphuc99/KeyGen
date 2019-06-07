#include "Snake.h"
#include "Point2D.h"
#include "Matrix.h"

Snake::Snake(Point2D start, Matrix* matrix)
{
	this->position.push_back(start);
	this->matrix = matrix;
}

Point2D Snake::getCurrentPosition()
{
	return Point2D(this->position[0].x, this->position[0].y);
}

bool Snake::isMovable(char x, char y, Matrix::state current_destination)
{
	if (!this->matrix->isValid(x, y))
	{
		return false;
	}

	for (char i = 0, size = this->position.size(); i < size; i++)
	{
		if (this->position[i].x == x && this->position[i].y == y)
		{
			return false;
		}
	}

	Matrix::state cur_state = this->matrix->getValue(x, y);
	return (cur_state == Matrix::FREE || cur_state == current_destination);
}

bool Snake::hasArrived(char x, char y, Matrix::state current_destination)
{
	Matrix::state cur_state = this->matrix->getValue(x, y);
	return (cur_state == current_destination);
}


void Snake::unmove(char x, char y)
{
//	this->this->position.push_back(last_move);
	this->position.erase(this->position.begin());
}

void Snake::move(char x, char y)
{
//	this->last_move = *(this->position.end());
	this->position.pop_back();
	this->position.insert(this->position.begin(), Point2D(x, y));
}
