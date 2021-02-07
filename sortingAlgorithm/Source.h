#pragma once
#include <filesystem>
#include <vector>
#include <list>
#include <string>
#include <fstream>
#include <random>
#include <iterator>
#include <algorithm>
#include <thread>
#define  INF 10001
#define  M 5e6
#define N 1e9
using namespace std;
using namespace std::filesystem;
/* function prototypes */

void sortFiles(string fileFirstS, string fileSecondS);

void createRandomNumbers()
{
	double lower_bound = 0;
	double upper_bound = 10000;
	uniform_real_distribution<double> unif(lower_bound, upper_bound);
	default_random_engine re;
	
	fstream fout("temp",fstream::ate);
	for (int i=0;i<N;i++)
	{
		double randomNumber = unif(re);
		fout<< randomNumber<<" ";

		if (i%10000000==0)
		{
			cout << i <<"  ";
		}
	}
}



void mergeTwoFiles()
{
	fstream tmp("temp1\\merge0" , fstream::in );
	fstream tmp2("temp1\\merge1", fstream::in);
	fstream tmp3("temp1\\mergeA", fstream::out);
	
	while (!tmp.eof() && !tmp2.eof())
	{
		double g,f;
		while (tmp.eof() && !tmp2.eof())
		{
			tmp >> g;
			tmp3 << g << " ";
		} 
		while (tmp2.eof() && !tmp.eof())
		{
			tmp2 >> g;
			tmp3 << g << " ";
		}

		tmp >> g;
		tmp2 >> f;
		if (g<f)
		{
			tmp3 << g<<" ";
		} 
		else
		{
			tmp3 << f << " ";
		}

	}
}

void mergeFiles()
{
	vector<string> files;
	string path = "temp1";
	for (auto &p : directory_iterator(path))
	{
		files.push_back(p.path().filename().string());
	}
	int x = 0;
	while (x+1<=files.size())
	{
		thread FThread(sortFiles, files[x], files[x + 1]);
		x+=2;
		thread SThread(sortFiles, files[x], files[x + 1]);
		x += 2;
		thread TThread(sortFiles, files[x], files[x + 1]);
		x += 2;
		thread FourthThread(sortFiles, files[x], files[x + 1]);
		x += 2;
		FThread.join();
		SThread.join();
		TThread.join();
		FourthThread.join();
	}
	
}


void sortFiles(string fileFirstS, string fileSecondS)
{
	fstream fileFirst("temp1\\" + fileFirstS, fstream::in);
	fstream fileSecond("temp1\\" + fileSecondS, fstream::in);
	fstream newFile("temp1\\" + fileFirstS+"_"+fileSecondS, fstream::out);
	if (!fileFirst.is_open()|| !fileSecond.is_open())
	{
		cout << "error";
	}
	double first = 0;
	double second = 0;
	while (!fileFirst.eof() && !fileSecond.eof())
	{
		fileFirst >> first;
		fileSecond >> second;
		if (first<second)
		{
			newFile << first<<" ";
		} 
		else
		{
			newFile << second << " ";
		}
	}
	fileFirst.close();
	fileSecond.close();
	newFile.close();
}


void mergeAll()
{
	//тут можно while
	mergeFiles( );
	//тут тоже
	thread threadMergeTwoFiles1(mergeTwoFiles); // TODO another count of threads
	thread threadMergeTwoFiles2(mergeTwoFiles);
	threadMergeTwoFiles1.join();
	threadMergeTwoFiles2.join();
	mergeTwoFiles();
	//erase temp
}