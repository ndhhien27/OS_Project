#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <conio.h>
#include <ctime>
#include <iomanip>
#include <cstring>
#include <omp.h>
using namespace std;
class DijkstraParallel_Omp {
public:
	DijkstraParallel_Omp();
	int doParallel();
	void input();
	void ParallelTrace();
	int length();
private:
	int numV, temp;
	int numth, md, mv;
	int inf = 27101997;
	int startV, endV;
	int **V;
	bool *connected;
	int *pV;
	char *path;
	int *mind;	//min distance
};