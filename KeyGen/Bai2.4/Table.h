#include "Bit.h"
#include <vector>
class Table
{
public:
	static Table* createTable();
	int operator[](int pos);
	~Table();
private:
	static Table* manage_table_value;
	vector<unsigned int>  table_value;
	Table();
};

