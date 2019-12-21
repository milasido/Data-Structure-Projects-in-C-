#include <iostream>
#include <string>
#include <fstream>
#include "ArgumentManager.h"
#include <algorithm>

using namespace std;

//function length
int lcs(string a, string b, int row, int col)
{
	//create len table
	int result;
	int **len = new int *[row + 1];
	for (int k = 0; k <= row; k++)
		len[k] = new int[col + 1];
	//loop to fill len table
	for (int i = 0; i <= row; i++)
		for (int j = 0; j <= col; j++)
		{
			if (i == 0 || j == 0)
				len[i][j] = 0;
			else if (a[i - 1] == b[j - 1])
				len[i][j] = 1 + len[i - 1][j - 1];
			else
				len[i][j] = max(len[i - 1][j], len[i][j - 1]);
		}
	result = len[row][col];

	//deallocate memory after using
	for (int i = 0; i <= row; i++)
	{
		delete[] len[i];
	}
	delete[] len;
	len = nullptr;
	return result;
}



/// main
int main(int argc, char* argv[])
//int main()
{
	ArgumentManager am(argc, argv);
	string input = am.get("input");
	string output = am.get("output");

	//string input;
	//cin >> input;
	//string output="out.txt";

	int l1, l2, l3, l4, l5, l6;
	int j = 0;

	//2d array to store strings
	string **arr = new string*[4];
	for (int i = 0; i < 4; i++)
		arr[i] = new string[1000];

	//read and store strings to array
	string line;
	ifstream ifs;
	ifs.open(input);

	while (getline(ifs, line))
	{
		if (!line.empty())
		{
			*arr[j] = line;
			j++;
		}
	}

	//write file
	ofstream ofs;
	ofs.open(output);
	if (j == 0)
		ofs << "Len: 0";
	else if (j == 1)
		ofs << "Len: " << arr[0]->length();
	else if (j == 2)
	{
		l1 = lcs(*arr[0], *arr[1], arr[0]->length(), arr[1]->length());
		ofs << "Len: " << l1;
	}
	else if (j == 3)
	{
		l1 = lcs(*arr[0], *arr[1], arr[0]->length(), arr[1]->length());
		l2 = lcs(*arr[0], *arr[2], arr[0]->length(), arr[2]->length());
		l3 = lcs(*arr[1], *arr[2], arr[1]->length(), arr[2]->length());
		ofs << "Len: " << min({ l1,l2,l3 });
	}
	else if (j == 4)
	{
		l1 = lcs(*arr[0], *arr[1], arr[0]->length(), arr[1]->length());
		l2 = lcs(*arr[0], *arr[2], arr[0]->length(), arr[2]->length());
		l3 = lcs(*arr[0], *arr[3], arr[0]->length(), arr[3]->length());
		l4 = lcs(*arr[1], *arr[2], arr[1]->length(), arr[2]->length());
		l5 = lcs(*arr[1], *arr[3], arr[1]->length(), arr[3]->length());
		l6 = lcs(*arr[2], *arr[3], arr[2]->length(), arr[3]->length());
		ofs << "Len: " << min({ l1,l2,l3,l4,l5,l6 });
	}
	else
		ofs << "Len: unknown (input should be 4 lines or less)";

	ofs.close();
	ifs.close();

	//deallocate memory
	for (int i = 0; i < j; ++i)
	{
		delete[] arr[i];
	}
	delete[] arr;
	arr = nullptr;
	return 0;
}