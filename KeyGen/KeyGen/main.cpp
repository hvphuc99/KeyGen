#include <iostream>
using namespace std;
#include <string>
#include <stdlib.h>
unsigned int convert4bytesToInt(unsigned char* bytes)
{
	unsigned int result = *(int*)bytes;
	return result;
}

void convertIntTo4bytes(unsigned char* bytes, unsigned int num)
{
	bytes[3] = (num >> 24) & 0xFF;
	bytes[2] = (num >> 16) & 0xFF;
	bytes[1] = (num >> 8) & 0xFF;
	bytes[0] = num & 0xFF;
}

unsigned char hashFunction(unsigned char arr[8], unsigned char key)
{
	unsigned int x = convert4bytesToInt(arr);
	unsigned int y = convert4bytesToInt(arr + 4);
	x = (x * 24001) % 22027;
	y = (y * 21661) % 20897;
	convertIntTo4bytes(arr, x);
	convertIntTo4bytes(arr + 4, y);
	return (x + y) % key;
}

// a[i] = false => 23
bool* getValidateArray(unsigned char username[8], unsigned int size)
{
	const unsigned char hash_array = 4;
	bool* validate_array = new bool[size];
	for (int i = 0; i < size; i++)
	{
		validate_array[i] = (hashFunction(username, hash_array) == 0) ? false : true;
	}
	return validate_array;
}

unsigned int formulating(unsigned int Const, unsigned int x, unsigned int y)
{
	return (x * Const + y);
}

struct KeyCondition
{
	unsigned int x, y, check_value, hash_value;
	bool* validate_array;
	KeyCondition(unsigned hash_value, unsigned int x, unsigned int y, unsigned int check_value, bool* validate_arry)
	{
		this->hash_value = hash_value;
		this->x = x;
		this->y = y;
		this->check_value = check_value;
		this->validate_array = validate_array;
	}
	bool isKey()
	{
		return formulating(this->hash_value, this->x, this->y) == this->check_value;
	}
	bool isValid()
	{
		return validate_array[formulating(this->hash_value, this->x, this->y)];
	}
};
string keyGenerate(string key, KeyCondition *key_condition)
{

}

void keyGenerator(string& key, KeyCondition *key_condition)
{
	
}

string generateKey(unsigned char username[8])
{
	const unsigned char hash_key = 14;

	unsigned char hash_value = hashFunction(username, hash_key);
	
	unsigned int size = (hash_value + hash_key);
	size = size * size;

	bool* validate_array = getValidateArray(username, size);

	unsigned char value_2 = hashFunction(username, hash_value);	// B0
	unsigned char value_1 = hashFunction(username, hash_value);	// AC
	unsigned char value_3,	// B4
		value_4;	// B8

	while ((value_3 = hashFunction(username, hash_value)) == value_1);
	while ((value_4 = hashFunction(username, hash_value)) == value_2);

	// check if (AC * hash_value + B0 == B4 * hash_value + B8)
	unsigned int check_value = formulating(hash_value, value_3, value_4);

	// check condition = f(a, 1, 2) == check_value = f(a, 3, 4)
	// key condition = arr[f(a,1,2)] = true
	
	KeyCondition key_condition(hash_value, value_1, value_2, check_value, validate_array);
	string key = "";
	keyGenerator(key, &key_condition);
	return key;
}


void main()
{
	//int arr[] = { 20,20,20,20,20,23,20,20,20,23,20,20,23,20,20,23,20,20,23,23,20,23,20,23,20,23,23,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,23,20,23,20,20,20,23,20,20,20,20,20,20,23,20,23,23,20,20,23,20,20,23,20,20,20,20,20,20,23,20,20,23,20,23,23,20,20,20,23,20,23,20,20,23,20,20,20,20,20,23,20,23,20,23,20,20,20,20,23,20,23,20,23,20,20,20,20,23,20,20,23,20,20,23,20,23,23,20,20,20,23,20,23,20,23,20,20,23,23,23,20,23,20,20,20,20,20,20,20,20,20,20,20,20,20,20,23,20,20,20,23,20,20,20,23,20,23,20,23,20,20,20,23,20,20,20,20,20,23,20,20,23,20,23,20,20,23,23,20,20,20,20,20,20,23,20,20,23,20,20,20,23,20,23,20,20,20,20,23,23,20,23,20,66,20,20,23,23,20,20,20,23,20,20,20,20,20,20,23,20,23,23,20,23,20,23,20,20,20,23,20,20,20,23,20,20,23,20,23,20,23,20,23,20,20,20,20,20,23,23,20,20,20,20,23,20,23,20,20,20,20,23,20,20,23,20,20,23,20,23,23,20,20,20,20,23,23,20,20,20,20,20,20,20,23,20,20,20,20,20,23,20,20,23,20,23,20,20,20,23,20,20,23,20,20,20,20,20,20,20,20,23,23,20,20,20,20,23,20,20,23,23,23,20,20,20,23,20,20,23,20,23,20,20,20,20,23,20,20,20,20,23,20,20,23,20,20,23,23,23,20,20,20,20,20,23,23,23,20,23,20,20,20,20,20,20,20,23,20,23,20,23,20,23,20,23,23,20,23,23,23,20,23,20,20,20,20,20,23,23,23,20,23,20,23,20,20,20,20,20,20,23,20,20,20,20,20,20,20,20,23,23,20,23,23,20,20,20,20,20,20,20,20,23,20,23,20,20,20,23,23,20,23,23,23,20,20,20,20,20,23,23,73,23,23,20,20,20,23,20,20,23,20,20,20,20,20,20,23,20,20,20,20,20,20,23,20,20,20,20,20,20,20,20,20,20,20,20,23,23,20,20,20,20,20,23,20,20,20,20,20,20,20,20,20,20,20,20,20,23,20,20,20,20,20,20,20,23,23,20,20,20,20,20,20,20,20,23,23,20,23,23,20,23,23,23,20,20,20,23,20,20,23,20,20,23,20,20,20,23,23,20,20,20,23,23,20,20,23,20,23,20,20,20,20,20,20,20,20,23,20,20,20,20,20,23,20,20,20,20,20,23,20,20,20,23,20,20,23,20,23,20,20,20,23,23,20,20,23,20,23,20,20,20,20,23,20,20,20,20,23,23,20,20,20,20,20,20,20,20,20,20,20,20,20 };
	//int x = 18;
	//int y = 2;
	//string key;
	//findKey(x, y, arr, key);
	//system("pause");
	unsigned char username[8];

	cout << "Nhap vao username: ";
	cin >> username;

	string key = generateKey(username);

	cout << "Key cua ban la: " << key << endl;

}