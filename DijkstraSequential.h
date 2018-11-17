#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <conio.h>
#include <ctime>
#include <iomanip>
#include <cstring>
using namespace std;
class DijkstraSequential {
public:
	DijkstraSequential();
	int do_Seq_Dijkstra();
	void input();
	void Seq_Trace();
	void Print_Way();
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
