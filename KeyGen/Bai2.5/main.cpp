#include <iostream>
#include <string>
#include <vector>


using namespace std;

class Point2D
{
public:
	Point2D(int x, int y)
	{
		this->x = x;
		this->y = y;
	}

	int x, y;

};



class Matrix
{
public:
	static enum state { SNAKE, FOOD, DESTINATION, FREE };

public:
	Matrix(string username)
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
			if (this->matrix[x_snake][y_snake] == FOOD || this->matrix[x_snake][y_snake] == DESTINATION)
			{
				break;
			}
			position--;
		}
		this->matrix[x_snake][y_snake] = SNAKE;
		snake.push_back(Point2D(x_snake, y_snake));
	}

	bool isMovable(char x, char y)
	{

	}

	void move(char x, char y)
	{

	}
	int getNumberOfFood()
	{
		return this->food.size();
	}

	~Matrix()
	{
		for (int i = 0; i < this->size; i++)
		{
			delete[] this->matrix[i];
		}
		delete[] this->matrix;
	}
private:
	state** matrix;
	const int size = 16;
	vector<Point2D> food;
	vector<Point2D> snake;
};

class KeyGenerator
{
public:
	KeyGenerator(string username)
	{
		this->matrix = new Matrix(username);
	}

	~KeyGenerator()
	{
		delete this->matrix;
	}

	string get()
	{
		return "";
	}
private:
	Matrix* matrix;
};

void main()
{
	string username;
	while (true)
	{
		int len = 0;
		while (len > 10 || len == 0)
		{
			cout << "Nhap vao username: ";
			cin >> username;
			len = username.length();
		}

		KeyGenerator key_gen(username);
		string key = key_gen.get();

		cout << "Key cua ban la: " << key << endl;
	}
}