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
#define  M 5// m5e6
#define N 30 //1e9
using namespace std;
using namespace std::filesystem;
/* function prototypes */

void sortFiles(string fileFirstS, string fileSecondS);

void renameAll()
{
	string path = "temp1\\";
	vector<string> files;
	for (auto& p : directory_iterator(path))
	{
		files.push_back(p.path().filename().string());
	}
	for (int i=0;i<files.size();i++)
	{
		rename(path+files[i], path+to_string(i));
	}
}
void deleteOldFiles(vector<string>& files, int x)
{
	for (int i = 0; i < x; i++)
	{
		string filename = "temp1\\" + files[i];
		if (remove(filename.c_str()) == 0) {
			cout << "Файл " << filename << " удален\n";
		}
		else {
			cerr << "Ошибка: " << '\n';
		}
	}
}

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


int mergeFiles()
{
	vector<string> files;
	string path = "temp1";
	while (true)
	{
		for (auto &p : directory_iterator(path))
		{
			files.push_back(p.path().filename().string());
		}

		int x = 0;

		if (files.size() == 1)// если файлы закончились
		{
			return 0;
		}
		if (x+1<files.size()&& x + 7 >= files.size())
		{
			sortFiles(files[x], files[x + 1]);
			x += 2;
		}
		
		while (x + 7 < files.size())
		{
			thread FThread(sortFiles, files[x], files[x + 1]);// TODO сделать норм, разделять файлы по 4 группы и сортировать группы
			x += 2;
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
		
		
		deleteOldFiles(files, x);
		renameAll();
		files.clear();
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
	fileFirst >> first;
	fileSecond >> second;
	while (!fileFirst.eof() && !fileSecond.eof())
	{

		if (first<second)
		{
			newFile << first<<" ";
			fileFirst >> first;
		} 
		else
		{
			newFile << second << " ";
			fileSecond >> second;
		}
	}
	while (!fileSecond.eof())
	{	
		newFile << second << " ";
		fileSecond >> second;
	}
	while (!fileFirst.eof())
	{	
		newFile << first << " ";
		fileFirst >> first;
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



	//erase temp
}