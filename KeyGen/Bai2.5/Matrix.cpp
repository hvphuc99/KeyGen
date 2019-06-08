#include "Matrix.h"
// #include "Snake.h"


Matrix::Matrix(string username)
{
	// init matrix
	this->matrix = new state * [this->size];
	for (int i = 0; i < this->size; i++)
	{
		this->matrix[i] = new state[this->size];
		for (int j = 0; j < this->size; j++)
		{
			this->matrix[i][j] = state::FREE;
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

	// num_of_foods = username.length();

	for (int i = 0, length = username.length(); i < length; i++)
	{
		unsigned char x_food, y_food;
		position = username[i] ^ hash;

		x_food = position / this->size;
		y_food = position % this->size;
		this->matrix[x_food][y_food] = state::FOOD;
		this->foods.push_back(Point2D(x_food, y_food));
		while (true)
		{
			// cal position
			hash -= position;
			// add food				// do again if position = 0
			if (hash != 0)
				break;
			hash--;
		}

	}

	// calculate destination
	hash = hash ^ position;
	unsigned char x_destination = 0, y_destination = 0;

	while (true)
	{
		position -= hash;

		x_destination = position / this->size;
		y_destination = position % this->size;

		if (this->matrix[x_destination][y_destination] != state::FOOD)
		{
			break;
		}
		hash--;
	}
	this->matrix[x_destination][y_destination] = state::DESTINATION;
	this->destination = Point2D(x_destination, y_destination);

	// calculate snake start

	position = hash;
	unsigned char x_snake = 0, y_snake = 0;

	while (true)
	{
		x_snake = position / this->size;
		y_snake = position % this->size;
		if (this->matrix[x_snake][y_snake] != state::FOOD && this->matrix[x_snake][y_snake] != state::DESTINATION)
		{
			break;
		}
		position--;
	}

	// init snake
	snake = Point2D(x_snake, y_snake);
	this->matrix[x_snake][y_snake] = state::SNAKE;

	this->print();
}

int Matrix::getNumberOfFood()
{
	return foods.size();
}

//bool Matrix::isValid(char x, char y)
//{
//	return (x >= 0 && x < this->size && y >= 0 && y < this->size);
//}
//
//state Matrix::getValue(char x, char y)
//{
//	return this->matrix[x][y];
//}
//
//
//void Matrix::setValue(char x, char y, state value)
//{
//	this->matrix[x][y] = value;
//}

Matrix::~Matrix()
{
	for (int i = 0; i < this->size; i++)
	{
		delete[] this->matrix[i];
	}
	delete[] this->matrix;

}

void Matrix::print()
{
	for (int i = 0; i < this->size; i++)
	{
		for (int j = 0; j < this->size; j++)
		{
			switch (this->matrix[i][j])
			{
			case state::SNAKE:
				cout << "99 ";
				break;
			case state::FOOD:
				cout << "CC ";
				break;
			case state::DESTINATION:
				cout << "DD ";
				break;
			case state::FREE:
				cout << "00 ";
				break;
			}
		}
		cout << endl;
	}
}


Point2D Matrix::getStartPoisition()
{
	return this->snake;
}

Point2D Matrix::getFood(char i)
{
	return this->foods[i];
}

Point2D Matrix::getDestination()
{
	return this->destination;
}
