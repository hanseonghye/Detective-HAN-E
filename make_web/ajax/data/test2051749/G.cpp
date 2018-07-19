#include <iostream>
#include <fstream>
#define MAX 50
using namespace std;

int path[MAX + 1][MAX + 1];
int next_path[MAX + 1][MAX + 1];

int main(void) {
	ifstream inFile("eleccar.inp");
	ofstream outFile("eleccar.out");

	int N, NEG_INF = -99999, INF = 99999, max = 0, start = 0, end = 0;

	inFile >> N;

	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			inFile >> path[i][j];
			if (path[i][j] != 99999)
				next_path[i][j] = j;
		}
	}

	for (int k = 1; k <= N; k++) {
		for (int i = 1; i <= N; i++) {
			for (int j = 1; j <= N; j++) {
				if (path[i][j] > path[i][k] + path[k][j]) {
					path[i][j] = path[i][k] + path[k][j];
					next_path[i][j] = next_path[i][k];
				}
			}
		}
	}

	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			if (i >= j) continue;
			if (max < path[i][j]) {
				max = path[i][j];
				start = i; end = j;
			}
		}
	}

	for (int k = 1; k <= N; k++) {
		for (int i = 1; i <= N; i++) {
			for (int j = 1; j <= N; j++) {
				if (path[i][k] + path[k][j] < path[i][j])
					path[i][j] = NEG_INF;
			}
		}
	}

	if (path[start][end] == NEG_INF) {
		outFile << "nega-cycle" << endl;
		return 0;
	}

	if (path[start][end] == INF) {
		outFile << "99999" << endl;
		return 0;
	}

	if (path[start][end] != NEG_INF && path[start][end] != INF) {
		int route;
		outFile << path[start][end] << endl;
		outFile << start << " ";
		route = next_path[start][end];
		while (1) {
			outFile << route << " ";
			if (route == end) break;
			route = next_path[route][end];
		}
		outFile << endl;
	}
	return 0;
}