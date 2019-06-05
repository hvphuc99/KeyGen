#pragma once
#include <iostream>
using namespace std;
#include "Hash.h"



class Key
{
public:
	Key();
	unsigned int hashKey(string _4Char_first);
	string find4CharFirstOfKey();
	vector<string> find8CharRestOfKey();
	void findKey();
private:
	Table *table_inst;
};

