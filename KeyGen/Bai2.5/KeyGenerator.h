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

	bool keySearching(char x, char y, state current_destination);
	bool keySearching();
	
	string get();
	char toHex(char x);
	string convertPathToKey(string path);
private:
	Matrix* matrix;
	Snake* snake;
	string key;
	string path;
};


