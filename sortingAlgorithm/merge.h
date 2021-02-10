#pragma once
#include <iostream>
#include <filesystem>
#include <vector>
#include <string>
#include <fstream>
#include <random>
#include <iterator>
#include <algorithm>
#include <thread>
#define  M 5e7
#define N 1e9 
using namespace std;
using namespace std::filesystem;


void sortFiles(string fileFirstS, string fileSecondS);

int mergeFiles();

void createRandomNumbers(int n);

void merge(vector<double>& arr, int l, int m, int r);

void createChunks(vector<double>& vec, fstream& fin);

bool makeDir();

void MergeSort(vector<double>& vec, int left, int right);

void printListToFile(vector<double>& vec, int i);

void printList(vector<double>& vec);

void renameAll();

void deleteOldFiles(vector<string>& files, int x);