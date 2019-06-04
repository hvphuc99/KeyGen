#pragma once
#include <string>
using namespace std;
class Hash
{
public:
	Hash(string arg);
	unsigned char* hash4ByteTo8Byte();
	
private:
	string str_input;
};

