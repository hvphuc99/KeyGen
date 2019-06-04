#include "Bit.h"

Bit::Bit(unsigned int num)
{
	this->number = num;
}

int Bit::getBitsLast(int numberOfBit)
{
	int result = 0;
	int tmp = 0;
	for (int i = 0; i < numberOfBit; i++) {
		tmp = this->number | (tmp << i);
		result = result | tmp;
		tmp = 0;
	}
	return result;
}
