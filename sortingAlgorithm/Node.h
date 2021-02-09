#pragma once
#include "Source.h"

void merge(vector<double> &arr, int l, int m, int r)
{
	int n1 = m - l + 1;
	int n2 = r - m;

	// Create temp arrays
	vector<double> L(n1);
	vector<double> R(n2);

	// Copy data to temp arrays L[] and R[]
	for (int i = 0; i < n1; i++)
		L[i] = arr[l + i];
	for (int j = 0; j < n2; j++)
		R[j] = arr[m + 1 + j];

	// Merge the temp arrays back into arr[l..r]

	// Initial index of first subarray
	int i = 0;

	// Initial index of second subarray
	int j = 0;

	// Initial index of merged subarray
	int k = l;

	while (i < n1 && j < n2) {
		if (L[i] <= R[j]) {
			arr[k] = L[i];
			i++;
		}
		else {
			arr[k] = R[j];
			j++;
		}
		k++;
	}

	// Copy the remaining elements of
	// L[], if there are any
	while (i < n1) {
		arr[k] = L[i];
		i++;
		k++;
	}

	// Copy the remaining elements of
	// R[], if there are any
	while (j < n2) {
		arr[k] = R[j];
		j++;
		k++;
	}
}




void createChunks(vector<double> &vec, fstream& fin)
{
	double g;
	for (int i = 0; i < M; i++)
	{
		fin >> vec[i];
	}
}bool makeDir()
{
	const char dir[] = "temp1";
	error_code ec;
	if (is_directory("temp1"))
		return is_directory(status(dir));
	else
		return create_directories(dir, ec);
}

void MergeSort(vector<double> &vec, int left,int right) {
	if (left >= right) {
		return;//returns recursively
	}
	int m = left + (right - left) / 2;
	MergeSort(vec, left, m);
	MergeSort(vec, m + 1, right);
	merge(vec, left, m, right);
}

void printListToFile(vector<double>& vec, int i)
{
	string s = "temp1\\" + to_string(i);
	fstream fout(s.c_str(), fstream::out);
	for (int i = 0; i < vec.size(); i++)
	{
		fout << vec[i]<<" ";
	}
}

void printList(vector<double>& vec)
{
	for (int i = 0; i < vec.size(); i++)
	{
		cout << vec[i]<<" ";
	}
}