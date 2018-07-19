#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <cstring>

#define clean() tmp.clear(), memset(visited, false, sizeof(visited));

using namespace std;

int N, v_size;
vector<int> ans, tmp, adj[51];
bool visited[51], cutVertex[51];
bool flag = false;

void ReadFile();
void find_food();
void WriteFile();

void dfs(int v) {
	visited[v] = true;
	tmp.push_back(v);
	if (cutVertex[v] && flag) return;
	for (int i = 0; i < adj[v].size(); i++) {
		if (!visited[adj[v][i]]) {
			dfs(adj[v][i]);
		}
	}
}

void ReadFile() {
	ifstream inFile("food.inp");
	int tmp1, tmp2;
	inFile >> N;
	for (int i = 0; i < N; i++) {
		inFile >> tmp1;
		while (inFile >> tmp2) {
			if (tmp2 == 0)	break;
			adj[tmp1].push_back(tmp2);
		}
	}
	inFile.close();
}

void find_food() {
	for (int i = 1; i <= N; i++) {
		dfs(i);
		v_size = tmp.size() - 1;
		clean();
		visited[i] = 1;
		dfs(adj[i][0]);
		if (tmp.size() != v_size)	cutVertex[i] = true;
		clean();
	}
	flag = true;
	for (int i = 1; i <= N; i++) {
		if (cutVertex[i])	continue;
		dfs(i);
		sort(tmp.begin(), tmp.end());
		if (tmp.size() > ans.size() || (tmp.size() == ans.size() && ans > tmp)) ans = tmp;
		clean();
	}
}

void WriteFile() {
	ofstream outFile("food.out");
	for (int i = 0; i < ans.size(); i++) {
		outFile << ans[i] << " ";
	}
}

int main(){
	ReadFile();
	find_food();
	WriteFile();
	return 0;
}