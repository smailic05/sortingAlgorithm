#pragma once
#include <filesystem>
#include <vector>
#include <list>
#include <string>
#include <fstream>
#include <random>
#define N 10e9
using namespace std;

void merge(int m, int l, int middle)
{
	fstream fin(to_string(m), fstream::in);
	vector<int> first;
	vector<int> second;
	


}

void mergeSort(int m, int l)
{
	if (m >= l)
	{
		return;
	}
	int middle = m + (l - m) / 2;
	mergeSort(m, middle);
	mergeSort(middle + 1, l);
	merge(m,l,middle);
}

void createChunks()
{

}

void createRandomNumbers()
{
	double lower_bound = 0;
	double upper_bound = 10000;
	uniform_real_distribution<double> unif(lower_bound, upper_bound);
	default_random_engine re;
	fstream fout("temp",fstream::out);
	for (int i=0;i<N;i++)
	{
		fout<< unif(re);
	}
}

//bool makeDir(const char * dir)
//{
//	error_code ec;
//	if ((dir))
//		return is_directory(status(dir));
//	else
//		return create_directories(dir, ec);
//}