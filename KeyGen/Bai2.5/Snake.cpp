//#include "Snake.h"
//#include "Point2D.h"
//#include "Matrix.h"
//
//
//Snake::Snake(Matrix* matrix)
//{
//	this->matrix = matrix;
//}
//
//Point2D Snake::getCurrentPosition()
//{
//	return Point2D(this->position.front().x, this->position.front().y);
//}
//
//bool Snake::isMovable(char x, char y, state current_destination)
//{
//	if (!this->matrix->isValid(x, y))
//	{
//		return false;
//	}
//	if (this->position.empty())
//	{
//		return true;
//	}
//
//	state cur_state = this->matrix->getValue(x, y);
//
//	for (const auto &position_i: this->position)
//	{
//		if (position_i.x == x && position_i.y == y)
//		{
//			return false;
//		}
//	}
//
//	return (cur_state == state::FREE || cur_state == current_destination);
//}
//
//bool Snake::hasArrived(char x, char y, state current_destination)
//{
//	state cur_state = this->matrix->getValue(x, y);
//	return (cur_state == current_destination);
//}
//
//
//void Snake::unmove()
//{
//	if (this->position.empty() || this->last_move.empty())
//	{
//		return;
//	}
//	// remove current position
//	this->position.pop_front();
//	// add last pos from stack
//	this->position.push_back(last_move.top());
//	// remove last pos from stack
//	this->last_move.pop();
//
//	//this->position.erase(this->position.begin());
//}
//
//void Snake::increaseLength()
//{
//	// them vao cuoi
//	this->position.push_back(this->last_move.top());
//	this->last_move.pop();
//}
//
//void Snake::move(char x, char y)
//{
//	if (!this->position.empty())
//	{
//		// them phan tu cuoi vao last move
//		this->last_move.push(this->position.back());
//		// loai bo phan tu cuoi
//		this->position.pop_back();
//	}
//	// them pos hien tai vao dau
//	this->position.push_front(Point2D(x, y));
//}
