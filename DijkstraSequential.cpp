#include "DijkstraSequential.h"
void Seq_export_file(int**V, int numV);
DijkstraSequential::DijkstraSequential()
{
	cout << "Nhap so dinh: ";
	cin >> numV;
	cout << "Nhap diem bat dau va ket thuc: ";
	cin >> startV >> endV;

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

	Seq_export_file(V, numV);
}
void DijkstraSequential::input()
{
	cout << numV << " " << startV << " " << endV << endl;
	for (int i = 0; i < numV; i++) {
		for (int j = 0; j < numV; j++)
			cout << setw(3) << V[i][j];
		cout << endl;
	}
}

int DijkstraSequential::do_Seq_Dijkstra()
{

	int inf = 27101997;
	int i, j;
	int md, mv;

	pV = new int[numV];
	connected = new bool[numV];
	mind = new int[numV];

	for (i = 0; i < numV; i++) {
		connected[i] = false;
		mind[i] = V[startV][i];
		pV[i] = startV;
	}

	connected[startV] = true;

	while (!connected[endV]) {


		for (i = 0; i < numV; i++) {
			if (!connected[i] && mind[i] < inf)
				break;
		}

		for (j = 0; j < numV; j++) {
			if (!connected[j] && mind[i] > mind[j])
				i = j;
		}
		mv = i;

			connected[mv] = true;
			for (i = 0; i < numV; i++) {
				if (!connected[i])
				{
						if (mind[mv] + V[mv][i] < mind[i])
						{
							mind[i] = mind[mv] + V[mv][i];
							pV[i] = mv;
						}
				}
			}

	}

	return mind[endV];
}


void DijkstraSequential::Seq_Trace()
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
}

void DijkstraSequential::Print_Way() {
	int len = do_Seq_Dijkstra();
	if (len > 0) {
		cout << "Length from " << startV << " to " << endV << " is: " << len << endl;
		cout << path;
	}
	else cout << "No way !";
}

void Seq_export_file(int **V, int numV)
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

//int DijkstraSequential::length()