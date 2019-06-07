#include "KeyGenerator.h"
#include "Matrix.h"
#include "Point2D.h"
#include "Snake.h"


bool KeyGenerator::keySearching(char x, char y, state current_destination)
{
	if (this->snake == NULL)
	{
		this->snake = new Snake(this->matrix);
	}

	if (!this->snake->isMovable(x, y, current_destination))
	{
		return false;
	}
	this->snake->move(x, y);
	if (this->snake->hasArrived(x, y, current_destination))
	{
		return true;
	}
	this->matrix->setValue(x, y, state::VISITED);
	if (this->keySearching(x - 1, y, current_destination))
	{
		this->matrix->setValue(x, y, state::FREE);
		this->path = '1' + this->path;
		return true;
	}
	if (this->keySearching(x + 1, y, current_destination))
	{
		this->matrix->setValue(x, y, state::FREE);
		this->path = '0' + this->path;
		return true;
	}
	if (this->keySearching(x, y + 1, current_destination))
	{	
		this->matrix->setValue(x, y, state::FREE);
		this->path = '3' + this->path;
		return true;
	}
	if (this->keySearching(x, y - 1, current_destination))
	{
		this->matrix->setValue(x, y, state::FREE);
		this->path = '2' + this->path;
		return true;
	}
	this->matrix->setValue(x, y, state::FREE);
	this->snake->unmove();

}

bool KeyGenerator::keySearching()
{
	Point2D current_position;
	for (int i = 0, size = this->matrix->getNumberOfFood(); i < size; i++)
	{
		if (this->snake == NULL)
		{
			current_position = *this->matrix->getStartPoisition();
		}
		else {
			current_position = this->snake->getCurrentPosition();
			this->snake->unmove();
		}
		this->path = "";
		if (keySearching(current_position.x, current_position.y, state::FOOD))
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
	if (keySearching(current_position.x, current_position.y, state::DESTINATION))
	{
		this->key += this->convertPathToKey(this->path);
	}
	else
	{
		return false;
	}

	return true;
}

string KeyGenerator::get()
{
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
	for (char i = 0, len = path.length(); i < len; i++)
	{
		char j = i;
		char move = 0;
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



KeyGenerator::KeyGenerator(string username)
{
	this->matrix = new Matrix(username);
	this->snake = NULL;
}


KeyGenerator::~KeyGenerator()
{
	delete this->matrix;
	if (this->snake != NULL)
		delete this->snake;
}
