#include "Hash.h"

Hash::Hash(string arg)
{
	this->str_input = arg;
}

string Hash::hash4ByteTo8Byte()
{
	unsigned int edx = *(unsigned int*)this->str_input.c_str(); //convert 4 byte char to int
	unsigned int eax = 0xd1fc1e8f;
	unsigned int ecx = 0xc6ef3720;
	unsigned int ebx = 0x3beabc9a;
	unsigned int esi, edi;
	while (ecx != 0) {
		esi = ebx;
		esi = esi << 4;
		edi = ebx;
		edi = edi >> 5;
		esi = esi ^ edi;
		esi = esi + ebx;
		edi = ecx;
		edi = edi >> 11; //0x0B = 11
		edi = edi & 3;
		if (edi == 0) edi = edx;
		else edi = 0;
		edi = edi + ecx;
		esi = esi ^ edi;
		eax = eax - esi;
		ecx = ecx - 0x9e3779b9;
		esi = eax;
		esi = esi << 4;
		edi = eax;
		edi = edi >> 5;
		esi = esi ^ edi;
		esi = esi + eax;
		edi = ecx;
		edi = edi & 3;
		if (edi == 0) edi = edx;
		else edi = 0;
		edi = edi + ecx;
		esi = esi ^ edi;
		ebx = ebx - esi;
		
		
	}
	string result;
	for (int i = 0; i < 4; i++) {
		result.push_back(ebx & 0xff);
		ebx = ebx >> 8;
	}
	for (int i = 4; i < 8; i++) {
		result.push_back(eax & 0xff);
		eax = eax >> 8;
	}
	return result;
}

unsigned int Hash::hash8ByteTo4Byte(Table *table_inst)
{
	string esi = this->str_input;
	unsigned int ebx = 0xffffffff;
	unsigned int ecx;
	for (int edx = 0; edx < 8; edx++) {
		ecx = 0;
		ecx = esi[edx];
		ecx = ecx ^ ebx;
		ecx = ecx & 0xff;
		ebx = ebx >> 8;
		ebx = ebx ^ (*table_inst)[ecx];
	}
	ebx = ~ebx;
	return ebx;
}
