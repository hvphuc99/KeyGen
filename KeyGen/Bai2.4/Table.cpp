#include "Table.h"

Table *Table::manage_table_value = NULL;

Table * Table::createTable()
{
	if (manage_table_value == NULL) {
		manage_table_value = new Table;

		unsigned int ecx, cl; //cl contain 8 bit last of ecx
		unsigned int eax = 0;
		for (int esi = 0; esi < 0x100; esi++) {
			eax = esi;
			for (int edx = 8; edx > 0; edx--) {
				ecx = eax;
				Bit tmp(ecx);
				cl = tmp.Bit::getBitsLast(8);
				if ((cl & 1) == 0) 
				{
					eax = eax >> 1;
				}
				else
				{
					ecx = ecx >> 1;
					ecx = ecx ^ 0xEDB88320;
					eax = ecx;
				}
			}
			manage_table_value->table_value.push_back(eax);
		}
	}
	return manage_table_value;
}

unsigned int Table::operator[](int pos)
{
	return manage_table_value->table_value[pos];
}

Table::~Table()
{
	delete manage_table_value;
}

Table::Table()
{
}
