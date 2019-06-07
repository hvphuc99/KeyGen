#include "KeyGenerator.h"
#include "Matrix.h"
#include "Point2D.h"
#include "Snake.h"


bool KeyGenerator::keySearching(char x, char y, Matrix::state current_destination)
{
	if (!this->snake->isMovable(x, y, current_destination))
	{
		return false;
	}
	if (this->snake->hasArrived(x, y, current_destination))
	{
		return true;
	}
	this->matrix->setValue(x, y, Matrix::VISITED);
	this->snake->move(x, y);
	if (this->keySearching(x + 1, y, current_destination))
	{
		this->matrix->setValue(x, y, Matrix::FREE);
		this->path = '0' + this->path;
		return true;
	}
	if (this->keySearching(x - 1, y, current_destination))
	{
		this->matrix->setValue(x, y, Matrix::FREE);
		this->path = '1' + this->path;
		return true;
	}
	if (this->keySearching(x, y - 1, current_destination))
	{
		this->matrix->setValue(x, y, Matrix::FREE);
		this->path = '2' + this->path;
		return true;
	}
	if (this->keySearching(x, y + 1, current_destination))
	{
		this->matrix->setValue(x, y, Matrix::FREE);
		this->path = '3' + this->path;
		return true;
	}
	this->matrix->setValue(x, y, Matrix::FREE);
	this->snake->unmove(x, y);

}

bool KeyGenerator::keySearching()
{
	Point2D current_position;
	for (int i = 0, size = this->matrix->getNumberOfFood(); i < size; i++)
	{
		current_position = this->snake->getCurrentPosition();
		this->path = "";
		if (keySearching(current_position.x, current_position.y, Matrix::FOOD))
		{
			this->key += this->path;
		}
		else
		{
			return false;
		}
	}

	current_position = this->snake->getCurrentPosition();
	this->path = "";
	if (keySearching(current_position.x, current_position.y, Matrix::DESTINATION))
	{
		this->key += this->path;
	}
	else
	{
		false;
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
		while (path[i] == path[j])
		{
			i++;
		}

		char move = j - i + 1;
		key = key + toHex(path[i] - '0' + 4 * (move - 1));
	}
}



KeyGenerator::KeyGenerator(string username)
{
	this->matrix = new Matrix(username);
	this->snake = this->matrix->getSnake();
}


KeyGenerator::~KeyGenerator()
{
	delete this->matrix;
}
