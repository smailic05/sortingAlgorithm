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
void pushToVec(vector<double> &vec, string s)
{
	fstream tmp(s, fstream::in );
		if (!tmp.is_open())
		{
			cout << "error pushvec";
		}
 	for (int i=0;i<vec.size();i++)
	{

		tmp>>vec[i];
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

void mergeFiles(string dir, int q)
{
	vector<double> vecFirst(M,INF);
	vector<double> vecsecond(M, INF);
	vector<double> templM;
	fstream create("temp1\\merge" + dir, fstream::out );
	create.close();
	for (int i=q;i<q+50;i++)
	{
		fstream tmp("temp1\\merge" + dir, fstream::out | fstream::app |fstream::in);
		pushToVec(vecsecond, "temp1\\" + to_string(i));
		pushToVec(vecFirst, "temp1\\merge" + dir);
		
		if (!tmp.is_open())
		{
			cout << "error mergeTwo";
		}

		int first = 0,
			sec = 0,
			c = 0;
		// нужно сделать пока чанк не закончиться потом новый чанк брать
		//иначе никак
		while ( sec <M )
		{
			if (first==M)
			{
				for (int i = 0; i < vecFirst.size(); i++)
				{
					tmp >> vecFirst[i];
				}
				first = 0;
			}
			
			if (vecFirst[first] <= vecsecond[sec])
			{
				if (vecFirst[first] < INF)
				{
					templM.push_back(vecFirst[first]);
				}
					c++;
					first++;
			}
			else 
			{
				tmp<<vecsecond[sec];
				c++;
				sec++;
			}

			
		}
		for (int i = 0; i < templM.size(); i++)
		{
			tmp << templM[i]<<" ";
		}
		templM.clear();
	}


}


void mergeAll()
{
	//тут можно while
	thread mergeF(mergeFiles, "0", 0);
	thread mergeS(mergeFiles, "1", 50);
	thread mergeT(mergeFiles, "2", 100);
	thread mergeFourth(mergeFiles, "3", 150);// соединяем в один большой файл с отсорт чиислами
	mergeF.join();
	mergeS.join();
	mergeT.join();
	mergeFourth.join();
	//тут тоже
	thread threadMergeTwoFiles1(mergeTwoFiles); // TODO another count of threads
	thread threadMergeTwoFiles2(mergeTwoFiles);
	threadMergeTwoFiles1.join();
	threadMergeTwoFiles2.join();
	mergeTwoFiles();
	//erase temp
}