#include "Matrix.h"
#include "Snake.h"
#include <Windows.h>

Matrix::Matrix(string username)
{
	// init matrix
	this->matrix = new state *[this->size];
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

	username_length = username.length();


	for (int i = 0, length = username.length(); i < length; i++)
	{
		unsigned char x_food, y_food;
		position = username[i] ^ hash;
		do
		{
			x_food = position / this->size;
			y_food = position % this->size;
			hash -= position;
			if (this->matrix[x_food][y_food] != state::FOOD)
			{

				this->matrix[x_food][y_food] = state::FOOD;
				this->foods.push_back(Point2D(x_food, y_food));
				break;
			}
			else {
				// cal position
				// add food				// do again if position = 0
				if (hash != 0)
					break;
				hash--;
			}
		} while (true);

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
	des.x = x_destination;
	des.y = y_destination;
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
	//this->print();
}

int Matrix::getNumberOfFood()
{
	return foods.size();
}
bool Matrix::isKeyExist()
{
	return (foods.size() == username_length);
}
bool Matrix::isValid(char x, char y)
{
	return (x >= 0 && x < this->size && y >= 0 && y < this->size);
}

state Matrix::getValue(char x, char y)
{
	return this->matrix[x][y];
}


void Matrix::setValue(char x, char y, state value)
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

}

void Matrix::print()
{
	for (int i = 0; i < this->size; i++)
	{
		for (int j = 0; j < this->size; j++)
		{
			if (i == this->snake.x && j == this->snake.y) {
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_BLUE);
				cout << "99 ";
				continue;
			}
			switch (this->matrix[i][j])
			{
				/*case state::SNAKE:
					cout << "99 ";
					break;*/
			case state::FOOD:
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
				cout << "CC ";
				break;
			case state::DESTINATION:
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED);
				cout << "DD ";
				break;
			case state::FREE:
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN);
				cout << "00 ";
				break;
			}
		}
		cout << endl;
	}
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7);
}


Point2D Matrix::getStartPoisition()
{
	return this->snake;
}


