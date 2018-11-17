#include <iostream>
#include "DijktraParallel.h"
#include <stdio.h>
#include <omp.h>
using namespace std;
void main() {
	double startTime, endTime;
	//Dijkstra Parallel
	DijkstraParallel_Omp *dk = new DijkstraParallel_Omp();
	startTime = omp_get_wtime();
	cout << dk->doParallel() << endl;
	endTime = omp_get_wtime();
	cout << endl << endTime - startTime << endl;
	dk->ParallelTrace();
	_getch();
}