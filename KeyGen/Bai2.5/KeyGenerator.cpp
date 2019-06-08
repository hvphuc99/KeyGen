#include "KeyGenerator.h"
#include "Matrix.h"
#include "Point2D.h"
#include "Snake.h"


bool KeyGenerator::keySearching(char x, char y, state current_destination, Point2D des)
{


	/*if (!this->snake->isMovable(x, y, current_destination))
	{
		return false;
	}*/
	this->snake->move(x, y);
	if (this->snake->hasArrived(x, y, current_destination))
	{
		return true;
	}
	this->matrix->setValue(x, y, state::VISITED);
	Point2D tmp(x, y);
	int best = getBestMove(tmp, des, current_destination);
	if (best == 2)
	if (this->keySearching(x, y - 1, current_destination, des))
	{
		this->matrix->setValue(x, y, state::FREE);
		this->path = '2' + this->path;
		return true;
	}
	if (best == 1)
	if (this->keySearching(x - 1, y, current_destination, des))
	{
		this->matrix->setValue(x, y, state::FREE);
		this->path = '1' + this->path;
		return true;
	}
	if (best == 0)
	if (this->keySearching(x + 1, y, current_destination, des))
	{
		this->matrix->setValue(x, y, state::FREE);
		this->path = '0' + this->path;
		return true;
	}
	if (best == 3)
	if (this->keySearching(x, y + 1, current_destination, des))
	{	
		this->matrix->setValue(x, y, state::FREE);
		this->path = '3' + this->path;
		return true;
	}
	this->matrix->setValue(x, y, state::FREE);
	this->snake->unmove();
	return false;
}

bool KeyGenerator::keySearching()
{
	if (!this->matrix->isKeyExist()) {
		return false;
	}
	Point2D current_position;
	for (int i = 0, size = this->matrix->getNumberOfFood(); i < size; i++)
	{
		current_position = this->snake->getCurrentPosition();
		this->snake->unmove();
		this->path = "";
		this->sortFoods(current_position);
		Point2D fd = this->matrix->foods.front();
		this->matrix->foods.erase(this->matrix->foods.begin());
		if (keySearching(current_position.x, current_position.y, state::FOOD, fd))
		{
			this->snake->increaseLength();
			this->key += this->convertPathToKey(this->path);
			Point2D pos = this->snake->getCurrentPosition();
			this->matrix->setValue(pos.x, pos.y, state::FREE);
		}
		else
		{
			return false;
		}
	}

	current_position = this->snake->getCurrentPosition();
	this->snake->unmove();
	this->path = "";
	if (keySearching(current_position.x, current_position.y, state::DESTINATION, this->matrix->des))
	{
		string tmp = this->convertPathToKey(this->path);
		this->key += tmp;
	}
	else
	{
		return false;
	}

	return true;
}

int KeyGenerator::getBestMove(Point2D s, Point2D f, state current_destination)
{
	if (s.x != f.x) {
		if (s.x > f.x) {
			if (this->snake->isMovable(s.x - 1, s.y, current_destination))
				return 1;
			else {
				if (s.y > f.y)
					if (this->snake->isMovable(s.x, s.y - 1, current_destination))
						return 2;
					else
						if (this->snake->isMovable(s.x, s.y + 1, current_destination))
							return 3;
						else
							return -1;
				if (s.y <= f.y)
					if (this->snake->isMovable(s.x, s.y + 1, current_destination))
						return 3;
					else
						if (this->snake->isMovable(s.x, s.y - 1, current_destination))
							return 2;
						else
							return -1;
			}
		}
		else {
			if (this->snake->isMovable(s.x + 1, s.y, current_destination))
				return 0;
			else {
				if (s.y > f.y)
					if (this->snake->isMovable(s.x, s.y - 1, current_destination))
						return 2;
					else
						if (this->snake->isMovable(s.x, s.y + 1, current_destination))
							return 3;
						else
							return -1;
				if (s.y <= f.y)
					if (this->snake->isMovable(s.x, s.y + 1, current_destination))
						return 3;
					else
						if (this->snake->isMovable(s.x, s.y - 1, current_destination))
							return 2;
						else
							return -1;
			}
		}
	}
	else {
		if (s.y > f.y) {
			if (this->snake->isMovable(s.x, s.y - 1, current_destination))
				return 2;
			else {
				if (s.x > f.x)
					if (this->snake->isMovable(s.x - 1, s.y, current_destination))
						return 1;
					else
						if (this->snake->isMovable(s.x + 1, s.y, current_destination))
							return 0;
						else
							return -1;
				if (s.x <= f.x)
					if (this->snake->isMovable(s.x + 1, s.y, current_destination))
						return 0;
					else
						if (this->snake->isMovable(s.x - 1, s.y, current_destination))
							return 1;
						else
							return -1;
			}
		}
		else {
			if (this->snake->isMovable(s.x, s.y + 1, current_destination))
				return 3;
			else {
				if (s.x > f.x)
					if (this->snake->isMovable(s.x - 1, s.y, current_destination))
						return 1;
					else
						if (this->snake->isMovable(s.x + 1, s.y, current_destination))
							return 0;
						else
							return -1;
				if (s.x <= f.x)
					if (this->snake->isMovable(s.x + 1, s.y, current_destination))
						return 0;
					else
						if (this->snake->isMovable(s.x - 1, s.y, current_destination))
							return 1;
						else
							return -1;
			}
		}
	}
}

string KeyGenerator::get()
{
	this->matrix->print();
	if (keySearching())
	{
		return key;
	}
	else
	{
		return "unsolvable";
	}
}

char KeyGenerator::toHex(char x)
{
	if (x < 10)
	{
		return x + '0';
	}
	return (x > 16) ? 0 : ('A' + (x - 10));

}


string KeyGenerator::convertPathToKey(string path)
{
	string key = "";
	for (int i = 0, len = path.length(); i < len; i++)
	{
		int j = i;
		int move = 0;
		while (path[i] == path[j] && move < 4)
		{
			i++;
			move++;
		}
		i--;
		key = key + toHex(path[i] - '0' + 4 * (move - 1));
	}
	return key;
}

void KeyGenerator::sortFoods(Point2D sr)
{
	for (int i = 0; i < this->matrix->foods.size(); i++) {
		float min = i;
		for (int j = i + 1; j < this->matrix->foods.size(); j++) {
			if (this->matrix->foods[j].distance(sr) < this->matrix->foods[min].distance(sr)) {
				min = j;
			}
		}
		Point2D tmp = this->matrix->foods[i];
		this->matrix->foods[i] = this->matrix->foods[min];
		this->matrix->foods[min] = tmp;
	}
}



KeyGenerator::KeyGenerator(string username)
{
	this->matrix = new Matrix(username);
	this->snake = new Snake(this->matrix);
	Point2D tmp(matrix->getStartPoisition());
	this->snake->move(tmp.x, tmp.y);
}


KeyGenerator::~KeyGenerator()
{
	delete this->matrix;
	if (this->snake != NULL)
		delete this->snake;
}
