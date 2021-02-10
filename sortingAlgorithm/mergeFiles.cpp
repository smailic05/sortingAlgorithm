#pragma once
#include "merge.h"

void createChunks(vector<double>& vec, fstream& fin)
{
	double g;
	for (int i = 0; i < vec.size(); i++)
	{
		fin >> vec[i];
	}
}

bool makeDir()
{
	const char dir[] = "temp1";
	error_code ec;
	if (is_directory("temp1"))
		return is_directory(status(dir));
	else
		return create_directories(dir, ec);
}

void printListToFile(vector<double>& vec, int i)
{
	string s = "temp1\\" + to_string(i);
	fstream fout(s.c_str(), fstream::out);
	for (int i = 0; i < vec.size(); i++)
	{
		fout << vec[i] << " ";
	}
}

void printList(vector<double>& vec)
{
	for (int i = 0; i < vec.size(); i++)
	{
		cout << vec[i] << " ";
	}
}

void renameAll()
{
	string path = "temp1\\";
	vector<string> files;
	for (auto& p : directory_iterator(path))
	{
		files.push_back(p.path().filename().string());
	}
	for (int i = 0; i < files.size(); i++)
	{
		rename(path + files[i], path + to_string(i));
	}
}
void deleteOldFiles(vector<string>& files, int x)
{
	for (int i = 0; i < x; i++)
	{
		string filename = "temp1\\" + files[i];
		if (remove(filename.c_str()) != 0) 
		{

			cerr << "error: " << '\n';
		}
	}
}

void createRandomNumbers(int n)
{
	double lower_bound = 0;
	double upper_bound = 10000;
	uniform_real_distribution<double> unif(lower_bound, upper_bound);
	default_random_engine re;

	fstream fout("temp", fstream::out);
	for (int i = 0; i < n; i++)
	{
		double randomNumber = unif(re);
		fout << randomNumber << " ";

	}
}


int mergeFiles()
{
	vector<string> files;
	string path = "temp1";
	while (true)
	{
		for (auto& p : directory_iterator(path))
		{
			files.push_back(p.path().filename().string());
		}

		int x = 0;

		if (files.size() == 1)// если файлы закончились
		{
			return 0;
		}
		if (x + 1 < files.size() && x + 7 >= files.size())
		{
			sortFiles(files[x], files[x + 1]);
			x += 2;
		}

		while (x + 7 < files.size())
		{
			thread FThread(sortFiles, files[x], files[x + 1]);
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
	fstream newFile("temp1\\" + fileFirstS + "_" + fileSecondS, fstream::out);
	if (!fileFirst.is_open() || !fileSecond.is_open())
	{
		cout << "error";
	}
	double first = 0;
	double second = 0;
	fileFirst >> first;
	fileSecond >> second;
	while (!fileFirst.eof() && !fileSecond.eof())
	{

		if (first < second)
		{
			newFile << first << " ";
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