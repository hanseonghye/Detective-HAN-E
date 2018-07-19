#include <iostream>
#include <cstdio>
#include <algorithm>
#include <fstream>
#include <string>
#include <stack>

using namespace std;
#define INF 99999
int A[51][51];
int D[51][51];
int P[51][51];

int main()
{
	ifstream inp("eleccar.inp");
	ofstream out("eleccar.out");
	int N;

	inp >> N;
	for (int i = 1; i <= N; ++i)
		for (int j = 1; j <= N; ++j) {
			inp >> A[i][j];
			D[i][j] = A[i][j];
			P[i][j] = i;
		}

	for (int k = 1; k <= N; ++k) {
		for (int i = 1; i <= N; ++i) {
			for (int j = 1; j <= N; ++j) {
				if (D[i][k] + D[k][j] < D[i][j]) {
					D[i][j] = D[i][k] + D[k][j];
					P[i][j] = P[k][j];
				}
			}
		}
	}

	for (int i = 1; i <= N; ++i) {
		if (D[i][i] < 0) {
			out << "nega-cycle" << endl;
			return 0;
		}
	}

	for (int i = 1; i <= N; ++i) {
		for (int j = 1; j <= N; ++j) {
			if (D[i][j] >= INF) {
				out << INF << endl;
				return 0;
			}
		}
	}

	int ans = -INF;
	int start;
	int end;
	for (int i = 1; i <= N; ++i) {
		for (int j = i + 1; j <= N; ++j) {
			if (ans < D[i][j]) {
				ans = D[i][j];
				start = i; end = j;
			}
		}
	}

	stack<int> path;
	path.push(end);

	int prev = P[start][end];
	//cout << prev << endl;
	while (prev != start) {
		path.push(prev);
		prev = P[start][prev];
	}
	path.push(start);

	out << ans << endl;
	while (!path.empty()) {
		out << path.top() << " ";
		path.pop();
	}
	out << endl;
	return 0;
}