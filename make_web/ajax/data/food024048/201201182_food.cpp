#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

int N;
vector<vector<int> > edges, bcc;
vector<int> dfn, par, low;
vector<bool> vis;
vector<vector<int> > ans;

int piv = 0, cpiv = 1;

void dfs(int x, int p)
{
	dfn[x] = low[x] = ++piv;
	par[x] = p;
	for (int i = 0; i < (int)edges[x].size(); i++) {
		int w = edges[x][i];
		if (w == p)
			continue;
		if (!dfn[w]) {
			dfs(w, x);
			low[x] = min(low[x], low[w]);
		}
		else {
			low[x] = min(low[x], dfn[w]);
		}
	}
}

void color(int x, int c) {
	if (c > 0)
		bcc[x].push_back(c);
	vis[x] = true;

	for (int i = 0; i < (int)edges[x].size(); i++) {
		int w = edges[x][i];
		if (vis[w])
			continue;
		if (dfn[x] <= low[w]) {
			bcc[x].push_back(++cpiv);
			color(w, cpiv);
		}
		else {
			color(w, c);
		}
	}
}
int main()
{
	ifstream ifs("food.inp");
	ofstream ofs("food.out");

	ifs >> N;
	edges.resize(N + 1);
	bcc.resize(N + 1);
	dfn.resize(N + 1);
	par.resize(N + 1);
	low.resize(N + 1);
	vis.resize(N + 1, false);

	int src, dest;
	for (int i = 0; i < N; i++) {
		ifs >> src;
		while (true) {
			ifs >> dest;
			if (dest == 0)
				break;
			edges[src].push_back(dest);
		}
	}

	dfs(1, 0);
	color(1, 0);

	ans.resize(cpiv+1);
	for (int i = 1; i <= N; i++) {
		for (int j = 0; j < (int)bcc[i].size(); j++) {
			ans[bcc[i][j]].push_back(i);
		}
	}

	int max = 0, maxI;
	for (int i = 0; i < (int)ans.size(); i++) {
		if (max < (int)ans[i].size()) {
			maxI = i;
			max = ans[i].size();
		}
	}

	for (int j = 0; j < max; j++)
		ofs << ans[maxI][j] << " ";
	ofs << endl;
}