#pragma once
#include <string>
#include "Matrix.h"

class Snake;
//class Matrix;
// enum class state;

using namespace std;
class KeyGenerator
{
public:
	KeyGenerator(string username);

	~KeyGenerator();

	bool keySearching(char x, char y, state current_destination, Point2D des);
	bool keySearching();
	
	int getBestMove(Point2D s, Point2D f, state current_destination);
	string get();
	char toHex(char x);
	string convertPathToKey(string path);
	void sortFoods(Point2D sr);
private:
	Matrix* matrix;
	Snake* snake;
	string key;
	string path;
};


