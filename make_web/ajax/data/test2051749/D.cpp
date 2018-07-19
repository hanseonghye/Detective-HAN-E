#include <cstdio>
#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>
#include <stack>
#include <utility>
#include <string.h>


#define MAX 99999
#define NIL -1

using namespace std;


int d1[501];
int N = 0;
int E = 0;
int a = 0;

vector<vector<pair<int, int> > > fw;
stack<int> path;
bool negaCycle = false;

struct Edge {
	int source;
	int dest;
	int weight;
};

struct Graph {
	int VC;
	int EC;
	struct Edge* edge;
};

struct Graph* createGraph(int VC, int EC) {
	struct Graph* graph =
		(struct Graph*)malloc(sizeof(struct Graph));
	graph->VC = VC;
	graph->EC = EC;

	graph->edge = (struct Edge*) malloc(graph->EC * sizeof(struct Edge));
	return graph;
}

void BellmanFord(struct Graph* graph, int src) {
	int VC = graph->VC;
	int EC = graph->EC;
	int dist[100];
	
	for (int i = 0; i < VC; i++)
		dist[i] = MAX;
	dist[src] = 0;

	for (int i = 1; i <= VC - 1; i++) {
		for (int j = 0; j < EC; j++) {
		
				int u = graph->edge[j].source;
				int v = graph->edge[j].dest;
				int w = graph->edge[j].weight;
				if (dist[u] != MAX && dist[u] + w < dist[v] )
					dist[v] = dist[u] + w;
		}
	}

	for (int i = 0; i < EC; i++) {
		int u = graph->edge[i].source;
		int v = graph->edge[i].dest;
		int w = graph->edge[i].weight;
		if (dist[u]!=MAX &&  dist[u] + w  <dist[v])
			negaCycle = true;
	}
	return;
}




int main() {
	ifstream fin("eleccar.inp");
	ofstream fout("eleccar.out");

	
	int D[50][50];  //cost
	int P[50][50];  //before Node
	int max = 0;
	int Src = 0;
	int Dst = 0;




	fin >> N;

	

	fw.resize(N + 1);
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			fw[i].push_back(make_pair(MAX, NIL));
			if (i == j) fw[i][j].first = 0;
		}
	}

	memset(P, 0, sizeof(int) * 2500);
	memset(D, 0, sizeof(int) * 2500);

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			fin >> D[i][j];
			if (D[i][j] != 0 && D[i][j] != 99999) {
				P[i][j] = i + 1;
				E++;
			}
		}
	}

	struct Graph* graph = createGraph(N, E);

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (D[i][j] != 0 && D[i][j] != 99999) {
				graph->edge[a].source = i;
				graph->edge[a].dest = j;
				graph->edge[a].weight = D[i][j];
				a++;
			}
		}
	}
	
	for (int i = 0; i < N; i++) {
		BellmanFord(graph, i);
	}

	for (int u = 0; u < N; u++) {
		for (int v = 0; v < N; v++) {
			fw[u][v].first = D[u][v];  //cost
			fw[u][v].second = u;       //SRC
		}
	}

	if (negaCycle) {
		fout << "nega-cycle";
	}


	

	else if (!negaCycle) {

		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				for (int k = 0; k < N; k++) {
					if (fw[k][j].first > fw[k][i].first + fw[i][j].first) {
						fw[k][j].first = fw[k][i].first + fw[i][j].first;
						fw[k][j].second = fw[i][j].second;

					}
				}
			}
		}



		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				if (max < fw[i][j].first && i<j) {
					max = fw[i][j].first;
					Src = i + 1;
					Dst = j + 1;
				}
			}
		}

		

	



		bool maxFlag = false;

		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				if (fw[i][j].first == MAX) maxFlag = true;
			}
		}
		if (maxFlag == true)  fout << "99999";



		if (!maxFlag) {
			fout << max << endl;
			for (int i = 0; i < N; i++) {
				for (int j = 0; j < N; j++) {
					if (fw[i][j].second == NIL) continue;
					else if (i + 1 == Src && j + 1 == Dst) {
						int pre = j;
						path.push(j + 1);
						while (i != fw[i][pre].second) {
							pre = fw[i][pre].second;
							path.push(pre + 1);
						}
						fout << i + 1 << " ";
						while (!path.empty()) {
							fout << path.top() << " ";
							path.pop();
						}
					}
				}
			}
		}
	}
}
