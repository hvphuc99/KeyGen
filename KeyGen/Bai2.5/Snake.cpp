#include "Snake.h"
#include "Point2D.h"
#include "Matrix.h"


Snake::Snake(Matrix* matrix)
{
	this->matrix = matrix;
}

Point2D Snake::getCurrentPosition()
{
	return Point2D(this->position[0].x, this->position[0].y);
}

bool Snake::isMovable(char x, char y, state current_destination)
{
	if (!this->matrix->isValid(x, y))
	{
		return false;
	}
	if (this->position.empty())
	{
		return true;
	}

	state cur_state = this->matrix->getValue(x, y);

	for (char i = 0, size = this->position.size(); i < size; i++)
	{
		if (this->position[i].x == x && this->position[i].y == y)
		{
			return false;
		}
	}

	return (cur_state == state::FREE || cur_state == current_destination);
}

bool Snake::hasArrived(char x, char y, state current_destination)
{
	state cur_state = this->matrix->getValue(x, y);
	return (cur_state == current_destination);
}


void Snake::unmove(char x, char y)
{
	if (position.empty())
	{
		return;
	}
	this->position.push_back(last_move);
	this->position.erase(this->position.begin());
}

void Snake::move(char x, char y)
{
	if (!this->position.empty())
	{
		this->last_move = this->position[this->position.size() - 1];
		this->position.pop_back();
	}
	this->position.insert(this->position.begin(), Point2D(x, y));
}
