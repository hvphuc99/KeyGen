#pragma once
#include <vector>
#include <iostream>
#include "Point2D.h"

class Snake;

using namespace std;
class Matrix
{
public:
	static const enum state{ SNAKE, FOOD, DESTINATION, FREE, VISITED };

public:
	Matrix(string username);

	int getNumberOfFood();
	

	bool isValid(char x, char y);
	state getValue(char x, char y);
	void setValue(char x, char y, state value);
	~Matrix();
	void print();
	Snake* getSnake();
private:
	state** matrix;
	const char size = 16;
	vector<Point2D> food;
	Snake* snake;
};
