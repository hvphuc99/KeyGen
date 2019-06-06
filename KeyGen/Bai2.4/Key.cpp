#define _CRT_SECURE_NO_WARNINGS
#include "Key.h"

namespace supportString {
	string upperCase(string str) {
		for (int i = 0; i < str.size(); i++) {
			if (str[i] >= 'a' && str[i] <= 'z') {
				str[i] -= 32;
			}
		}
		return str;
	}
}

Key::Key()
{
	this->table_inst = Table::createTable();
}

unsigned int Key::hashKey(string _4Char_first)
{
	Hash convert_4byte(_4Char_first);
	string _8byte_hash;
	_8byte_hash = convert_4byte.hash4ByteTo8Byte();

	Hash convert_8byte(_8byte_hash);
	return convert_8byte.hash8ByteTo4Byte(this->table_inst);
}

string Key::find4CharFirstOfKey()
{
	string _4Char_first = "aaaa";
	for (char i = 'A'; i <= 'Z'; i++) {
		_4Char_first[0] = i;
		for (char j = 'A'; j <= 'Z'; j++) {
			_4Char_first[1] = j;
			for (char z = 'a'; z <= 'z'; z++) {
				_4Char_first[2] = z;
				for (char e = '0'; e <= '?'; e++) {
					_4Char_first[3] = e;

					unsigned check = hashKey(_4Char_first);
					if (check == 0xb456b480) {
						return _4Char_first;
					}
				}
			}
		}
	}
}

vector<string> Key::find8CharRestOfKey()
{
	vector<string> result;
	string _8Char_rest("4a4a4a1d");
	for (char a2 = 'C'; a2 <= 'f'; a2++) {
		_8Char_rest[1] = a2;
		for (char a4 = 'C'; a4 <= 'f'; a4++) {
			_8Char_rest[3] = a4;
			for (char a6 = 'C'; a6 <= 'f'; a6++) {
				_8Char_rest[5] = a6;
				int count = 1;
				while (count <= 2) {
					if (count == 1)
						_8Char_rest[7] = 'd';
					else
						_8Char_rest[7] = 'D';
					string copy_8Char_rest = _8Char_rest;
					copy_8Char_rest = supportString::upperCase(copy_8Char_rest);
					Hash convert8Byte(copy_8Char_rest);
					unsigned int check = convert8Byte.hash8ByteTo4Byte(this->table_inst);
					if (check == 0xe367db0c) {
						result.push_back(_8Char_rest);
					}
					count++;
				}
			}
		}
	}
	return result;
}

void Key::findKey()
{
	string _4Char_first = find4CharFirstOfKey();
	vector<string> results_8Char_rest = find8CharRestOfKey();
	for (int i = 0; i < results_8Char_rest.size(); i++) {
		cout << "Key " << i + 1 << ": " << _4Char_first + results_8Char_rest[i] << endl;
	}
}

