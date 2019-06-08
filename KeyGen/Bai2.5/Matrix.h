#pragma once
#include <vector>
#include <iostream>
#include "Point2D.h"

class Snake;
enum class state { FOOD, DESTINATION, FREE, VISITED };

using namespace std;
class Matrix
{
public:

public:
	Matrix(string username);

	int getNumberOfFood();
	//D53CCC82DD2D9FFFBCC0	
	//CC02DDD9
	bool isValid(char x, char y);
	state getValue(char x, char y);
	void setValue(char x, char y, state value);
	~Matrix();
	void print();
	Point2D getStartPoisition();
	vector<Point2D> foods;
	bool isKeyExist();
	Point2D des;
private:
	state** matrix;
	const char size = 16;
	char username_length;
	char num_of_foods;
	Point2D snake;
};
