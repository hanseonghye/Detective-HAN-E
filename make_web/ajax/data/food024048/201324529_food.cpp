#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

#define NLL -1

using namespace std;


vector<int> vec;
vector<int>::iterator i;

unsigned int Maximum = 0;
int cnt = 0;
int num;

ifstream ifs;
ofstream ofs;

class Edge
{
public:
	int u;
	int v;
	Edge(int u, int v);
};
Edge::Edge(int u, int v)
{
	this->u = u;
	this->v = v;
}

class Graph
{
	int V;   
	int E;    
	vector<int> *adj;    
				
	void BCCUtil(int u, int disc[], int low[], vector<Edge> *st, int parent[]);
public:
	Graph(int V);   
	void add_Edge(int v, int w);   
	void BCC();   
	void inputGraph(int num);
	void has_Check(vector<int> *tmp, vector<Edge> *st);
	void is_Max(vector<int> tmp);

};

Graph::Graph(int V)
{
	this->V = V;
	this->E = 0;
	adj = new vector<int>[V];
}

void Graph::add_Edge(int v, int w)
{
	adj[v].push_back(w);
	E++;
}


void Graph::inputGraph(int num)
{
	int before = 0;
	for (int i = 0; i < num; i++) {
		while (true) {
			int tmp;
			ifs >> tmp;
			if (before == 0) {
				before = tmp;
				continue;
			}
			if (tmp == 0) {
				before = tmp;
				break;
			}
			else {
				add_Edge(before, tmp);
			}
		}
	}
}


void Graph::BCCUtil(int u, int disc[], int low[], vector<Edge> *sst,
	int parent[])
{
	
	static int time = 0;
	disc[u] = low[u] = ++time;
	int children = 0;
	vector<int> temp;
	vector<int>::iterator i;

	for (i = adj[u].begin(); i != adj[u].end(); ++i)
	{
		int v = *i;
		if (disc[v] == -1)
		{
			children++;
			parent[v] = u;
			sst->push_back(Edge(u, v));
			BCCUtil(v, disc, low, sst, parent);
			low[u] = min(low[u], low[v]);
			if ((disc[u] == 1 && children > 1) ||
				(disc[u] > 1 && low[v] >= disc[u]))
			{
				temp.clear();
				while (sst->back().u != u || sst->back().v != v)
				{
					has_Check(&temp, sst);
					sst->pop_back();
				}
				has_Check(&temp, sst);
				sst->pop_back();
				cnt++;

				sort(temp.begin(), temp.end());
				is_Max(temp);
			}
		}

		else if (v != parent[u] && disc[v] < low[u])
		{
			low[u] = min(low[u], disc[v]);
			sst->push_back(Edge(u, v));
		}
	}

}

void Graph::BCC()
{
	int *disc = new int[V];
	int *low = new int[V];
	int *parent = new int[V];
	vector<Edge> *st = new vector<Edge>[E];

	for (int i = 0; i < V; i++)
	{
		disc[i] = NLL;
		low[i] = NLL;
		parent[i] = NLL;
	}

	for (int i = 0; i < V; i++)
	{
		if (disc[i] == NLL)
			BCCUtil(i, disc, low, st, parent);
		int j = 0;	
		while (st->size() > 0)
		{
			j = 1;
			st->pop_back();
		}
		if (j == 1)
		{
			cout << endl;
			cnt++;
		}
	}
}

void Graph::has_Check(vector<int> *temp, vector<Edge> *sst)
{
	bool hasU = false;
	bool hasV = false;
	vector<int>::iterator i;

	for (i = temp->begin(); i != temp->end(); i++) {
		if (*i == sst->back().u)
			hasU = true;

	}
	if (!hasU)
		temp->push_back(sst->back().u);

	for (i = temp->begin(); i != temp->end(); i++) {
		if (*i == sst->back().v)
			hasV = true;
	}
	if (!hasV)
		temp->push_back(sst->back().v);

}

void Graph::is_Max(vector<int> temp)
{
	vector<int>::iterator i;

	if (temp.size() > Maximum) {
		vec.clear();
		for (i = temp.begin(); i != temp.end(); i++) {
			vec.push_back(*i);
		}
		Maximum = vec.size();
	}
	else if (temp.size() == vec.size()) {
		for (int i = 0; i < temp.size(); i++) {
			if (temp.at(i) > vec.at(i))
				break;
			else if (temp.at(i) == vec.at(i))
				continue;
			else {
				vec.clear();
				for (int j = 0; j < temp.size(); j++) {
					vec.push_back(temp.at(j));
				}
				break;
			}

		}
	}
}

void Input() {
	ifs.open("food.inp");
	ifs >> num;
}

void process() {
	Graph g(num + 1);
	g.inputGraph(num);
	g.BCC();
}
void Output() {
	ofs.open("food.out");
	for (i = vec.begin(); i != vec.end(); i++)
		ofs << *i << " ";
}
int main()
{
	Input();
	process();
	Output();
	return 0;
}

//참고한 사이트 : http://www.geeksforgeeks.org/biconnected-components/