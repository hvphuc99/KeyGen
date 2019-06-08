#include <iostream>
#include <string>
#include <stdlib.h>
#include <vector>
#include <string.h>
using namespace std;
class Hash {

public:
	static unsigned char bytes[8];
	static void setBytes(const unsigned char bytes[8])
	{
		copy(bytes, bytes + 8, Hash::bytes);
	}
	static unsigned int convert4bytesToInt(unsigned char* bytes)
	{
		unsigned int result = *(int*)bytes;
		return result;
	}

	static void convertIntTo4bytes(unsigned char* bytes, unsigned int num)
	{
		bytes[3] = (num >> 24) & 0xFF;
		bytes[2] = (num >> 16) & 0xFF;
		bytes[1] = (num >> 8) & 0xFF;
		bytes[0] = num & 0xFF;
	}

	static unsigned char hashFunction(unsigned char key)
	{
		unsigned int x = convert4bytesToInt(bytes);
		unsigned int y = convert4bytesToInt(bytes + 4);
		x = (x * 24001) % 22027;
		y = (y * 21661) % 20897;
		convertIntTo4bytes(bytes, x);
		convertIntTo4bytes(bytes + 4, y);
		unsigned int sum = x + y;
		unsigned int rem = sum % (unsigned int)key;
		return rem;
	}
};
unsigned char Hash::bytes[8];

class Point2D
{
public:
	Point2D(char x, char y)
	{
		this->x = x;
		this->y = y;
	}
	Point2D()
	{

	}
	char x, y;
};

class HashMatrix
{
public:
	const unsigned char hash_key = 20;
	const unsigned char hash_element_key = 4;
	static const enum state { OBSTACLE, MOVABLE, VISITED, SOURCE, DESTINATION };
public:
	HashMatrix(unsigned char username[8])
	{
		Hash::setBytes(username);

		//this->hash_value = Hash::hashFunction(hash_key);
		this->size = Hash::hashFunction(hash_key) + this->hash_key;

		this->matrix = new state * [size];
		for (int i = 0; i < size; i++)
		{
			this->matrix[i] = new state[size];
		}

		for (int i = 0; i < size; i++)
		{
			for (int j = 0; j < size; j++)
			{
				this->matrix[i][j] = (Hash::hashFunction(hash_element_key) == 0) ? OBSTACLE : MOVABLE;
			}
		}

		// evaluate source
		char x_source = Hash::hashFunction(this->size);
		char y_source = Hash::hashFunction(this->size);
		this->source = Point2D(x_source, y_source);

		// set source
		this->set(source.x, source.y, SOURCE);

		// evaluate destion
		char x_destination, y_destination;

		while ((x_destination = Hash::hashFunction(this->size)) == source.x);
		while ((y_destination = Hash::hashFunction(this->size)) == source.y);

		Point2D destination(x_destination, y_destination);

		// set destination
		this->set(destination.x, destination.y, DESTINATION);
	//	this->print();
	}
	void print()
	{
		for (int i = 0; i < size; i++)
		{
			for (int j = 0; j < size; j++)
			{
				switch (this->matrix[i][j])
				{
				case SOURCE:
					cout << 's';
					break;
				case DESTINATION:
					cout << 'f';
					break;
				case OBSTACLE:
					cout << '#';
					break;
				case MOVABLE:
					cout << '.';
					break;
				}
			}
			cout << endl;
		}
	}
	void set(int x, int y, enum state value)
	{
		this->matrix[x][y] = value;
	}

	bool isMovable(int x, int y)
	{
		return (x >= 0 && y >= 0 && x < this->size && y < this->size && this->matrix[x][y] != VISITED && this->matrix[x][y] != OBSTACLE);
	}

	bool hasArrived(int x, int y)
	{
		return (this->matrix[x][y] == DESTINATION);
	}

	Point2D getSource()
	{
		return this->source;
	}

	~HashMatrix()
	{
		for (int i = 0; i < size; i++)
		{
			delete[] matrix[i];
		}
		delete[] matrix;
	}

private:
	int size;
	int hash_value;
	enum state** matrix;
	Point2D source;
};


class KeyGenerator {
public:

	KeyGenerator(unsigned char username[8])
	{
		this->matrix = new HashMatrix(username);
		this->matrix->print();
	}

	bool keySearching(int x, int y)
	{
		if (!this->matrix->isMovable(x, y))
		{
			return false;
		}
		if (this->matrix->hasArrived(x, y))
		{
			return true;
		}
		this->matrix->set(x, y, HashMatrix::VISITED);

		if (this->keySearching(x - 1, y))
		{
			this->key = 'l' + this->key;
			return true;
		}

		if (this->keySearching(x + 1, y))
		{
			this->key = 'r' + this->key;
			return true;
		}

		if (this->keySearching(x, y + 1))
		{
			this->key = 'd' + this->key;
			return true;
		}

		if (this->keySearching(x, y - 1))
		{
			this->key = 'u' + this->key;
			return true;
		}
		this->matrix->set(x, y, HashMatrix::MOVABLE);
		return false;
	}


	string getKey()
	{
		Point2D source = this->matrix->getSource();
		return (this->keySearching(source.x, source.y)) ? key : "unsolvable";
	}
	~KeyGenerator()
	{
		delete this->matrix;
	}
private:
	HashMatrix* matrix;
	string key;
};

void main()
{
	unsigned char username[8] = { 0 };
	while (true)
	{
		int len = 0;
		while (len < 5 || len > 8)
		{
			cout << "Nhap vao username (5-8): ";
			cin >> username;
			len = strlen((const char *)username);
		}

		KeyGenerator key_gen(username);
		string key = key_gen.getKey();

		cout << "Key cua ban la: " << key << endl;
	}
}
