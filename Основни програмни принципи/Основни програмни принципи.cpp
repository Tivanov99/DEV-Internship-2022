// Основни програмни принципи.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
using namespace std;

int main()
{
	int v = 10;

	int* y;
	y = &v;
	cout << sizeof(*y) << "\n";
	y + 5;
	cout << sizeof(*y) << "\n";


	int arr[5] = { 1,2,3,4,5 };
	int* p = arr;

	for (size_t i = 0; i < 5; i++)
	{
		cout << *p << "\n";
		p++;
	}

}

