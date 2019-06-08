#pragma once
#include <string>
#include "Matrix.h"

// class Snake;
//class Matrix;
// enum class state;

using namespace std;
class KeyGenerator
{
public:
	KeyGenerator(string username);

	~KeyGenerator();

	string get();
	
private:
	//bool keySearching(char x, char y, state current_destination);
	bool keySearching();
	char toHex(char x);
	string convertPathToKey(string path);
	string getPath(Point2D source, Point2D destination);
private:
	Matrix* matrix;
	// Snake* snake;
	string key;
	string path;
};


