#include <iostream>
#include <string>
#include <vector>
#include "KeyGenerator.h"

using namespace std;

void main()
{
	string username;
	while (true)
	{
		int len = 0;
		while (len > 10 || len == 0)
		{
			cout << "Nhap vao username: ";
			cin >> username;
			len = username.length();
		}

		KeyGenerator key_gen(username);
		string key = key_gen.get();

		cout << "Key cua ban la: " << key << endl;
	}
}