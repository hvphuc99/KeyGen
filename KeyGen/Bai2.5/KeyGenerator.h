#pragma once
#include <string>

class Snake;
class Matrix;

using namespace std;
class KeyGenerator
{
public:
	KeyGenerator(string username);

	~KeyGenerator();

	bool keySearching(char x, char y, Matrix::state current_destination);
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


