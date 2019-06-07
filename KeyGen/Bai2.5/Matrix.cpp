
#include "Matrix.h"
#include "Snake.h"

Matrix::Matrix(string username)
{
	// init matrix
	this->matrix = new state * [this->size];
	for (int i = 0; i < this->size; i++)
	{
		this->matrix[i] = new state[this->size];
		for (int j = 0; j < this->size; j++)
		{
			this->matrix[i][j] = FREE;
		}
	}

	// generate matrix

	// find sum of username character
	unsigned char sum = 0;
	for (int i = 0, length = username.length(); i < length; i++)
	{
		sum += username[i];
	}

	// number of food = username.length()

	// calculate food position
	unsigned char hash = sum;
	unsigned char position = 0;

	for (int i = 0, length = username.length(); i < length; i++)
	{
		unsigned char x_food, y_food;
		position = username[i] ^ hash;

		x_food = position / this->size;
		y_food = position % this->size;
		this->matrix[x_food][y_food] = FOOD;
		while (true)
		{
			// cal position
			hash -= position;
			// add food				// do again if position = 0
			if (hash != 0)
				break;
			hash--;
		}

		this->food.push_back(Point2D(x_food, y_food));
	}

	// calculate destination
	hash = hash ^ position;
	unsigned char x_destination = 0, y_destination = 0;

	while (true)
	{
		position -= hash;

		x_destination = position / this->size;
		y_destination = position % this->size;

		if (this->matrix[x_destination][y_destination] != FOOD)
		{
			break;
		}
		hash--;
	}
	this->matrix[x_destination][y_destination] = DESTINATION;

	// calculate snake start

	position = hash;
	unsigned char x_snake = 0, y_snake = 0;

	while (true)
	{
		x_snake = position / this->size;
		y_snake = position % this->size;
		if (this->matrix[x_snake][y_snake] != FOOD && this->matrix[x_snake][y_snake] != DESTINATION)
		{
			break;
		}
		position--;
	}
	this->matrix[x_snake][y_snake] = SNAKE;

	// init snake
	this->snake = new Snake(Point2D(x_snake, y_snake), this);
	//this->print();
}

int Matrix::getNumberOfFood()
{
	return this->food.size();
}

bool Matrix::isValid(char x, char y)
{
	return !(x >= 0 && x < this->size && y >= 0 && y < this->size);
}

Matrix::state Matrix::getValue(char x, char y)
{
	return this->matrix[x][y];
}


void Matrix::setValue(char x, char y, Matrix::state value)
{
	this->matrix[x][y] = value;
}

Matrix::~Matrix()
{
	for (int i = 0; i < this->size; i++)
	{
		delete[] this->matrix[i];
	}
	delete[] this->matrix;

	delete this->snake;
}

void Matrix::print()
{
	for (int i = 0; i < this->size; i++)
	{
		for (int j = 0; j < this->size; j++)
		{
			switch (this->matrix[i][j])
			{
			case SNAKE:
				cout << "99 ";
				break;
			case FOOD:
				cout << "CC ";
				break;
			case DESTINATION:
				cout << "DD ";
				break;
			case FREE:
				cout << "00 ";
				break;
			}
		}
		cout << endl;
	}
}


Snake* Matrix::getSnake()
{
	return this->snake;
}
