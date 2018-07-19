#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <utility>
#include <stack>
#include <algorithm>

#define INF 99999
#define MAX 51

using namespace std;

int m[MAX][MAX];
int v[MAX];
string p[MAX][MAX];

int main(void) {
	/*
	ifstream fin("./sampleData4/3.inp");
	ofstream fout("eleccar.out");
	*/

	ifstream fin("eleccar.inp");
	ofstream fout("eleccar.out");
	int n, w;
	int max = -99999;
	int ax, ay;
	bool nega = false;

	fin >> n;

	for (int i = 1; i <= n; ++i)
		for (int j = 1; j <= n; ++j)
			m[i][j] = INF;

	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= n; ++j) {
			fin >> w;
			m[i][j] = w;
			p[i][j] = to_string(i) + " ";
			if (i == j) {
				m[i][j] = 0;
				p[i][j] = " ";
			}
		}
	}

	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= n; ++j) {
			for (int k = 1; k <= n; ++k) {
				if ((m[j][i] != INF && m[i][k] != INF) && (i != j && i != k)) {
					int tmp = m[j][i] + m[i][k];
					if (m[j][k] > tmp) {
						m[j][k] = tmp;
						p[j][k] = p[j][i] + p[i][k];
						v[k] = 1;
					}
					if (m[j][i] < 0 && m[i][k] < 0 && m[j][k] < 0)
						nega = true;
				}
			}
		}
	}


	for (int i = 1; i <= n; ++i) {
		for (int j = 1; j <= n; ++j) {
			if (max < m[i][j] && m[i][j] != INF && (i < j)) {
				max = m[i][j];
				ax = i; ay = j;
			}
		}
	}

	sort(v + 1, v + n + 1);

	if (!nega) {
		if (v[1] != 0) {
			fout << max << endl;
			fout << p[ax][ay] + to_string(ay) << endl;
		}
		else
			fout << INF << endl;
	}
	else
		fout << "nega-cycle" << endl;

	return 0;
}
