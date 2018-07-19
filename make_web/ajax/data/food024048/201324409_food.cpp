#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>

using namespace std;

vector<bool> visited;
vector<int> cutVertex;
vector<vector<int> > edgeList;
vector<vector<int> > BiconnectedComponnent;
vector<int> now, low;
int n = 1;
int bccn = 1;
void findCutVertex(int current, int before);
void findBiconnect(int current, int c);

int main() {
	int N = 0;
	ifstream fin("food.inp");
	string line;
	int tmpEdge;

	fin >> N;
	
	N++;
	edgeList.resize(N);
	visited.resize(N, false);
	BiconnectedComponnent.resize(N);
	now.resize(N);
	low.resize(N);
	getline(fin, line);

	for (int i = 0; i < N-1; i++) {
		getline(fin, line);
		istringstream iss(line);
		int num;
		iss >> num;
		vector<int> tmp_edge;
		while (iss >> tmpEdge) {
			if (tmpEdge != 0) tmp_edge.push_back(tmpEdge);
		}
		edgeList[num] = tmp_edge;
	}
	//
	findCutVertex(1, 0);
	//
	findBiconnect(1, 0);
	//
	int maxLength = 0;
	vector<vector<int> > sameLength;
	for (int i = 1; i < BiconnectedComponnent.size(); i++) {
		if (maxLength < BiconnectedComponnent[i].size()) {
			sameLength.clear();
			sameLength.push_back(BiconnectedComponnent[i]);
			maxLength = BiconnectedComponnent[i].size();
		}
		else if (maxLength == BiconnectedComponnent[i].size()) {
			sameLength.push_back(BiconnectedComponnent[i]);
		}
	}

	vector<vector<int> > result;
	result.resize(bccn + 1);
	for (int i = 1; i < N; i++) {
		for (int j = 0; j < BiconnectedComponnent[i].size(); j++) {
			result[BiconnectedComponnent[i][j]].push_back(i);
		}
	}
	maxLength = 0;
	int maxIndex;
	for (int i = 0; i < result.size(); i++) {
		if (maxLength < result[i].size()) {
			//
			maxLength = result[i].size();
			//
			maxIndex = i;
		}
	}
	ofstream fout("food.out");
	for (int i = 0; i < maxLength; i++) {
		fout << result[maxIndex][i] << " ";
	}
	return 0;
}

int min(int a, int b) {
	if (a > b) return b;
	return a;
}

void findCutVertex(int current, int before) {
	now[current] = n;
	low[current] = n++;

	for (int j = 0; j < edgeList[current].size(); j++) {
		int e = edgeList[current][j];
		if (e == before) {
			continue;
		}
		if (now[e] == 0) {
			findCutVertex(e, current);
			low[current] = min(low[current], low[e]);
		}
		else {
			low[current] = min(now[e], low[current]);
		}
	}
}

void findBiconnect(int current, int c) {

	visited[current] = true;
	
	if (c > 0) { BiconnectedComponnent[current].push_back(c); }
	
	for (int i = 0; i < edgeList[current].size(); i++) {
		int e = edgeList[current][i];
		if (visited[e]) { continue; }
		if (now[current] <= low[e]) {
			BiconnectedComponnent[current].push_back(++bccn);
			findBiconnect(e, bccn);
		}
		else {
			findBiconnect(e, c);
		}
	}
}