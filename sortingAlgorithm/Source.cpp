#include <iostream>
#include <filesystem>
#include <chrono>
#include <list>
#include "Source.h"
#include "Node.h"


using namespace std;

int main()
{
	
	createRandomNumbers(N);
	fstream fin("temp",fstream::in);
	vector<double> vec(M);
	for (int i = 0; i < N/M; i++)
	{
		createChunks(vec, fin);
		MergeSort(vec,0,M-1);
		printListToFile(vec, i);
	}

	mergeAll();


	return 0;
}