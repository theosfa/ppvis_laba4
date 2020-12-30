#include <iostream>

#include "matrix.h"

using namespace std;

int main()
{
	int** arr = new int* [4];
	for (int i = 0; i < 4; i++)
	{
		arr[i] = new int[4];
	}
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
		{
			arr[i][j] = 5;
		}
	matrix<int> test_matrix;
	test_matrix.init(arr, 4);
	test_matrix.print_matrix();
	cout << endl;
	test_matrix.add_vertex();
	test_matrix.print_matrix();
	cout << endl;
	test_matrix.deletion_vertex();
	test_matrix.print_matrix();
	cout << endl;
	test_matrix.change_connection_matrix(1, 1) = 999;
	test_matrix.print_matrix();
	cout << endl;
	matrix<int>::iterator al(test_matrix.begin());
	for (int i = 0; i < 16; i++)
	{
		cout << al<<endl;
		++al;
	}
}