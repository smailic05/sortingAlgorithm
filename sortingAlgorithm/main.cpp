#include <iostream>
#include <filesystem>
#include <chrono>
#include <list>
#include "merge.h"


int main()
{
	
	int n,m;
	char ch;
	cout << " input count of numbers to sort multiple of 20"<<endl;
	cin >> n;
	if (n<20)
	{
		cout << "too small count"<<endl;
		return 0;
	}
	m = n / 20;
	cout << "create new file with random numbers?"<<endl;
	cin >> ch;
	if (ch=='y')
	{
		createRandomNumbers(n);
	}
	
	makeDir();

	fstream fin("temp",fstream::in);
	vector<double> vec(m);
	for (int i = 0; i < n/m; i++)
	{
		createChunks(vec, fin);
		MergeSort(vec,0,m-1);
		printListToFile(vec, i);
	}

	mergeFiles();

	return 0;
}