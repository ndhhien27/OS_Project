#include "DijktraParallel.h"
void findNearest(int s, int e, int *mind, bool *connected, int *d, int *v);
void update_mind(int s, int e, int mv, bool *connected, int *mind, int**V, int *pV);
void export_file(int**V, int numV);
DijkstraParallel_Omp::DijkstraParallel_Omp()
{
	cout << "Nhap so dinh: ";
	cin >> numV;
	cout << "Nhap diem bat dau va ket thuc: ";
	cin >> startV >> endV;
	//cout << numV << startV << endV;

	V = new int*[numV];
	for (int i = 0; i < numV; i++)
		V[i] = new int[numV];

	for (int i = 0; i < numV; i++) {
		for (int j = 0; j < numV; j++) {
			temp = rand() % 98 + 2;
			if (i == j)
			{
				V[i][i] = 0;
			}
			else if ((i % 2 == 0 && j % 2 == 0) || (i % 2 != 0 && j % 2 != 0))
			{
				V[i][j] = inf;
			}
			else if (i > j) V[i][j] = V[j][i];
			else if (V[i][j] != inf) V[i][j] = temp;
		}
	}

	export_file(V, numV);
}
void DijkstraParallel_Omp::input()
{
	cout << numV << " " << startV << " " << endV << endl;
	for (int i = 0; i < numV; i++) {
		for (int j = 0; j < numV; j++)
			cout << setw(3) << V[i][j];
		cout << endl;
	}
}

int DijkstraParallel_Omp::doParallel()
{
	int myFirst, myLast;
	int my_id, my_md, my_mv;
	int i, j;
	int md, mv, numth;

	pV = new int[numV];
	connected = new bool[numV];
	mind = new int[numV];
	//connected[startV]=true;

	/*for (i = 0; i < numV; i++) {
		connected[i] = false;
	}*/

	for (i = 0; i < numV; i++) {
		connected[i] = false;
		mind[i] = V[startV][i];
		pV[i] = startV;
	}

	connected[startV] = true;

#pragma omp parallel private (myFirst, myLast, my_id, my_md, my_mv) 
	{
		my_id = omp_get_thread_num();
#pragma omp single
		{
			numth = omp_get_num_threads();
		}

		myFirst = (my_id*numV) / numth;
		myLast = ((my_id + 1)*numV) / numth - 1;

		while (!connected[endV]) {
#pragma omp single
			{
				md = inf;
				mv = -1;
			}

			findNearest(myFirst, myLast, mind, connected, &my_md, &my_mv);

#pragma omp critical
			{
				if (my_md < md) {
					md = my_md;
					mv = my_mv;
				}
			}
#pragma omp barrier

#pragma omp single
			{
				if (mv != -1) {
					connected[mv] = true;
				}
			}
#pragma omp barrier
			if (my_mv != -1) {
				update_mind(myFirst, myLast, mv, connected, mind, V, pV);
			}
#pragma omp barrier
		}
	}

	return mind[endV];
}

void findNearest(int s, int e, int *mind, bool *connected, int *d, int *v)
{
	int i;
	int inf = 27101997;
	*d = inf;
	*v = -1;
	for (i = s; i <= e; i++) {
		if (!connected[i] && mind[i] < *d) {
			*d = mind[i];
			*v = i;
		}
	}
	return;
}

void update_mind(int s, int e, int mv, bool *connected, int *mind, int**V, int *pV)
{
	int i;
	int inf = 27101997;

	for (i = s; i <= e; i++)
	{
		if (!connected[i])
		{
			if (V[mv][i] < inf)
			{
				if (mind[mv] + V[mv][i] < mind[i])
				{
					mind[i] = mind[mv] + V[mv][i];
					pV[i] = mv;
				}
			}
		}
	}
	return;
}

void DijkstraParallel_Omp::ParallelTrace()
{
	int i = endV;
	int *point = new int[numV];
	path = new char[10 * numV];
	int count = 0;

	point[count++] = i;
	while (i != startV) {
		i = pV[i];
		point[count++] = i;
	}

	strcpy(path, "");
	char temp[10];
	for (i = count - 1; i >= 0; i--) {
		sprintf(temp, "%d", point[i]);
		strcat(path, temp);

		if (i > 0) {
			sprintf(temp, " --> ");
			strcat(path, temp);
		}
	}

	cout << "done find path\n";
	cout << path << endl;
}

void export_file(int **V, int numV)
{
	int inf = 27101997;
	ofstream fo("C:/Users/kyure/source/repos/OSProject/Data/matrix1.txt");
	for (int i = 0; i < numV; i++) {
		for (int j = 0; j < numV; j++) {
			if (V[i][j] == inf) fo << left << setw(3) << 0;
			else fo << left << setw(3) << V[i][j];
		}
		if (i != (numV - 1)) fo << endl;
	}
}

//int DijkstraMultiThread::length()