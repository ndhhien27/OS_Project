#include <iostream>
#include "DijkstraSequential.h"
#include <stdio.h>
#include <omp.h>
using namespace std;
void main() {
	double startTime, endTime;

	//Dijkstra Sequential
	DijkstraSequential *dk = new DijkstraSequential();
	startTime = omp_get_wtime();
	cout << dk->do_Seq_Dijkstra() << endl;
	endTime = omp_get_wtime();
	dk->Seq_Trace();
	dk->Print_Way();
	_getch();
}