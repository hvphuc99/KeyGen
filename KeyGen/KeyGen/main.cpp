#include <iostream>
#include <string>
#include <stdlib.h>
#include <vector>
using namespace std;
class Hash {

public:
	static unsigned char bytes[8];
	static void setBytes(unsigned char bytes[8])
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
		unsigned int rem = sum % (unsigned int) key;
		return rem;
	}
};
unsigned char Hash::bytes[8];

class Formula
{
public:
	static int Const;
	static void setConst(int Const)
	{
		Formula::Const = Const;
	}
	static unsigned int get(unsigned int x, unsigned int y)
	{
		return (x * Const + y);
	}
};

int Formula::Const = 0;

class Validate
{
public:
	int size;
	bool* arr;

	// arr[i] = false <=> 23
	Validate(unsigned char hash_value, unsigned char hash_key)
	{
		this->size = (hash_value + hash_key);
		this->size = size * size;

		const unsigned char hash_validate = 4;

		this->arr = new bool[this->size];

		for (int i = 0; i < this->size; i++)
		{
			unsigned int tmp = Hash::hashFunction(hash_validate);
			this->arr[i] = (tmp == 0) ? false : true;
		}
	}
	~Validate()
	{
		if (arr != NULL)
			delete arr;
	}
	bool isValid(unsigned int x, unsigned int y)
	{
		int index = Formula::get(x, y);
		if (index < 0 || x < 0 || y < 0 || index >= size)
			return false;
		return arr[index];
	}
};

class KeyTest
{
public:
	unsigned int x, y, rx, ry;
	unsigned int check_value;
	Validate* validate;
	string key;

	// check if (AC * hash_value + B0 == B4 * hash_value + B8)

	// check condition = f(a, 1, 2) == check_value = f(a, 3, 4)
	// key condition = arr[f(a,1,2)] = true

	KeyTest(unsigned int x, unsigned int y, unsigned int rx, unsigned ry, Validate* validate)
	{
		this->key = "";

		this->x = x;
		this->y = y;

		this->rx = rx;
		this->ry = ry;

		this->validate = validate;

		this->check_value = Formula::get(this->rx, this->ry);
	}
	bool isKey()
	{
		return Formula::get(this->x, this->y) == this->check_value;
	}
	void getNextBestMoves(vector<unsigned char >& next_moves)
	{
		// value_1: {l: --, r: ++}
		// value_2: {u: --, d: ++}

		unsigned char moves[4] = { 'l', 'd', 'u', 'r' };
		for (int i = 0; i < 4; i++)
		{
			unsigned new_x = this->x;
			unsigned new_y = this->y;
			switch (moves[i])
			{
			case 'l':
				new_x--;
				break;
			case 'r':
				new_x++;
				break;
			case 'u':
				new_y--;
				break;
			case 'd':
				new_y++;
				break;
			}
			if (this->validate->isValid(new_x, new_y))
			{
				next_moves.push_back(moves[i]);
				// try to limit number of wrong direction moves
			}
		}

		// sort in order closeset to (rx, ry)
	}

	void addMove(unsigned char move)
	{
		key += move;
		// go to new state
		switch (move)
		{
		case 'l':
			this->x--;
			break;
		case 'r':
			this->x++;
			break;
		case 'u':
			this->y--;
			break;
		case 'd':
			this->y++;
			break;
		}
	}
	void removeLastMove()
	{
		char move = this->key.back();

		// back to new state
		switch (move)
		{
		case 'l':
			this->x++;
			break;
		case 'r':
			this->x--;
			break;
		case 'u':
			this->y++;
			break;
		case 'd':
			this->y--;
			break;
		}

		this->key.pop_back();
	}
};


class KeyGenerator {
public:
	unsigned char hash_value;
	const unsigned char hash_key = 20;

	KeyGenerator(unsigned char username[8])
	{
		Hash::setBytes(username);

		hash_value = Hash::hashFunction(hash_key);

		Formula::setConst(hash_value + hash_key);
	}

	bool keyGenerator(KeyTest* key_test)
	{
		if (key_test->isKey())
			return true;
		if (key_test->key.size() >= 25) {
			return false;
		}
		cout << key_test->key << endl;
		vector<unsigned char> next_moves;
		key_test->getNextBestMoves(next_moves);

		for (unsigned char move : next_moves)
		{
			key_test->addMove(move);
			if (keyGenerator(key_test))
				return true;
			key_test->removeLastMove();
		}

		return false;
	}


	string getKey()
	{
		Validate validate(hash_value, hash_key);
		hash_value += hash_key;
		unsigned char value_1 = Hash::hashFunction(hash_value);	// AC
		unsigned char value_2 = Hash::hashFunction(hash_value);	// B0
		unsigned char value_3,	// B4
			value_4;	// B8

		while ((value_3 = Hash::hashFunction(hash_value)) == value_1);
		while ((value_4 = Hash::hashFunction(hash_value)) == value_2);

		KeyTest key_test(value_1, value_2, value_3, value_4, &validate);

		return (this->keyGenerator(&key_test)) ? key_test.key : "not found";
	}
};

void main()
{
	//int arr[] = { 20,20,20,20,20,23,20,20,20,23,20,20,23,20,20,23,20,20,23,23,20,23,20,23,20,23,23,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,23,20,23,20,20,20,23,20,20,20,20,20,20,23,20,23,23,20,20,23,20,20,23,20,20,20,20,20,20,23,20,20,23,20,23,23,20,20,20,23,20,23,20,20,23,20,20,20,20,20,23,20,23,20,23,20,20,20,20,23,20,23,20,23,20,20,20,20,23,20,20,23,20,20,23,20,23,23,20,20,20,23,20,23,20,23,20,20,23,23,23,20,23,20,20,20,20,20,20,20,20,20,20,20,20,20,20,23,20,20,20,23,20,20,20,23,20,23,20,23,20,20,20,23,20,20,20,20,20,23,20,20,23,20,23,20,20,23,23,20,20,20,20,20,20,23,20,20,23,20,20,20,23,20,23,20,20,20,20,23,23,20,23,20,66,20,20,23,23,20,20,20,23,20,20,20,20,20,20,23,20,23,23,20,23,20,23,20,20,20,23,20,20,20,23,20,20,23,20,23,20,23,20,23,20,20,20,20,20,23,23,20,20,20,20,23,20,23,20,20,20,20,23,20,20,23,20,20,23,20,23,23,20,20,20,20,23,23,20,20,20,20,20,20,20,23,20,20,20,20,20,23,20,20,23,20,23,20,20,20,23,20,20,23,20,20,20,20,20,20,20,20,23,23,20,20,20,20,23,20,20,23,23,23,20,20,20,23,20,20,23,20,23,20,20,20,20,23,20,20,20,20,23,20,20,23,20,20,23,23,23,20,20,20,20,20,23,23,23,20,23,20,20,20,20,20,20,20,23,20,23,20,23,20,23,20,23,23,20,23,23,23,20,23,20,20,20,20,20,23,23,23,20,23,20,23,20,20,20,20,20,20,23,20,20,20,20,20,20,20,20,23,23,20,23,23,20,20,20,20,20,20,20,20,23,20,23,20,20,20,23,23,20,23,23,23,20,20,20,20,20,23,23,73,23,23,20,20,20,23,20,20,23,20,20,20,20,20,20,23,20,20,20,20,20,20,23,20,20,20,20,20,20,20,20,20,20,20,20,23,23,20,20,20,20,20,23,20,20,20,20,20,20,20,20,20,20,20,20,20,23,20,20,20,20,20,20,20,23,23,20,20,20,20,20,20,20,20,23,23,20,23,23,20,23,23,23,20,20,20,23,20,20,23,20,20,23,20,20,20,23,23,20,20,20,23,23,20,20,23,20,23,20,20,20,20,20,20,20,20,23,20,20,20,20,20,23,20,20,20,20,20,23,20,20,20,23,20,20,23,20,23,20,20,20,23,23,20,20,23,20,23,20,20,20,20,23,20,20,20,20,23,23,20,20,20,20,20,20,20,20,20,20,20,20,20 };
	//int x = 18;
	//int y = 2;
	//string key;
	//findKey(x, y, arr, key);
	//system("pause");
	unsigned char username[8] = { 0 };

	cout << "Nhap vao username: ";
	cin >> username;

	KeyGenerator key_gen(username);
	string key = key_gen.getKey();

	cout << "Key cua ban la: " << key << endl;
	system("pause");
}