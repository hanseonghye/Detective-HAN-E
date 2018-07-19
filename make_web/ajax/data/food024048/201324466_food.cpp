#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

int num, u, v, size_v;
vector <int> tmp;
vector <int> result;
vector <int> edge[51];
bool checked[51], cv[51];
bool flag = false;

void dfs(int);

int main()
{
	ifstream in("food.inp");
	ofstream out("food.out");
	in >> num;

	for (int i = 0; i < num; i++) {
		in >> u;
		while (in >> v) {
			if (v == 0) break;
			edge[u].push_back(v);
		}
	}

	for (int i = 1; i <= num; i++) {
		dfs(i);
		size_v = tmp.size() - 1;
		tmp.clear();
		for (int i = 0; i < 51; i++)
			checked[i] = false;

		checked[i] = true;
		dfs(edge[i][0]);

		if (tmp.size() != size_v)
			cv[i] = true;
		
		tmp.clear();
		for (int i = 0; i < 51; i++)
			checked[i] = false;
	}

	flag = true;

	for (int i = 1; i <= num; i++) {
		if (cv[i]) continue;
		dfs(i);


		if ((tmp.size() == result.size() && result > tmp) || tmp.size() > result.size())
			result = tmp;

		tmp.clear();
		for (int i = 0; i < 51; i++) {
			checked[i] = false;
		}
	}
	sort(result.begin(), result.end());
	for (int i = 0; i < result.size(); i++)
		out << result[i] << " ";

	return 0;
}

void dfs(int u) {
	checked[u] = true;
	tmp.push_back(u);
	if (cv[u] == true && flag == true) return;
	for (int v = 0; v < edge[u].size(); v++)
		if (!checked[edge[u][v]]) dfs(edge[u][v]);
}