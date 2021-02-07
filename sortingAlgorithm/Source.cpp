#include <iostream>
#include <filesystem>
#include <chrono>
#include <list>
#include "Source.h"
#include "Node.h"


using namespace std;

int main()
{

	fstream fin("temp1\\merge0",fstream::in);
	//for (int i = 0; i < N/M; i++)
	//{
 //       Node* a = NULL;
 //       createChunks(&a, fin);
 //       MergeSort(&a);
 //       printListToFile(a, i);
 //       deleteNode(&a);
	//}
	//std::fstream fs;
	//fs.open("test.txt", std::fstream::in | std::fstream::out | std::fstream::app);

	//fs << " more lorem ipsum";

	//fs.close();
	mergeAll();
					//mergeTwoFiles();
	//double prev,next;
	//fin >> prev;
	//while (fin.eof())
	//{
	//	fin >> next;
	//	if (next<prev)
	//	{
	//		cout << "error";
	//	}
	//}

	return 0;
}