#include "Hash.h"

Hash::Hash(string arg)
{
	this->str_input = arg;
}

unsigned char* Hash::hash4ByteTo8Byte()
{
	string copy_str_input = this->str_input;
	unsigned int edx = *(unsigned int*)copy_str_input.c_str(); //convert 4 byte char to int
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
		unsigned char result[9] = { 0 };
		for (int i = 0; i < 4; i++) {
			result[i] = ebx & 0xff;
			ebx = ebx << 8;
			result[i + 4] = eax & 0xff;
			eax = eax << 8;
		}
		return result;
	}
}
