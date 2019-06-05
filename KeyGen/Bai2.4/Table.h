#include "Bit.h"
#include <vector>
#include <iostream>
using namespace std;

class Table
{
public:
	static Table* createTable();
	unsigned int operator[](int pos);
	~Table();
private:
	static Table* manage_table_value;
	vector<unsigned int>  table_value;
	Table();
};

