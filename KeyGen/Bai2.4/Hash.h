#pragma once
#include "Table.h"
#include <string>
using namespace std;
class Hash
{
public:
	Hash(string arg);
	string hash4ByteTo8Byte();
	unsigned int hash8ByteTo4Byte(Table *table_inst);
private:
	string str_input;
};

