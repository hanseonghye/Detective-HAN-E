// A C++ program to find biconnected components in a given undirected graph
// Referenced at http://www.geeksforgeeks.org/biconnected-components/
#include <list>
#include <vector>
#include <algorithm>
#include <cstdio>
#include <stack>
#define NIL -1

using namespace std;

int cnt = 0;
int N;
vector <vector <int> > componentSet;
vector <int> resultComponent;
vector <int> tmpComponent;

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

// A class that represents an directed graph
class Graph
{
	int V;    // No. of vertices
	int E;    // No. of edges
	list<int> *adj;    // A dynamic array of adjacency lists

					   // A Recursive DFS based function used by BCC()
	void BCCUtil(int u, int disc[], int low[],
		list<Edge> *st, int parent[]);
public:
	Graph(int V);   // Constructor
	void addEdge(int v, int w);   // function to add an edge to graph
	void BCC();    // prints strongly connected components
};

Graph::Graph(int V)
{
	this->V = V;
	this->E = 0;
	adj = new list<int>[V];
}

void Graph::addEdge(int v, int w)
{
	adj[v].push_back(w);
	E++;
}

void Graph::BCCUtil(int u, int disc[], int low[], list<Edge> *st,
	int parent[])
{
	static int time = 0;

	disc[u] = low[u] = ++time;
	int children = 0;

	list<int>::iterator i;
	for (i = adj[u].begin(); i != adj[u].end(); ++i)
	{
		int v = *i;

		if (disc[v] == -1)
		{
			children++;
			parent[v] = u;

			st->push_back(Edge(u, v));
			BCCUtil(v, disc, low, st, parent);

			low[u] = min(low[u], low[v]);

			if ((disc[u] == 1 && children > 1) ||
				(disc[u] > 1 && low[v] >= disc[u]))
			{
				while (st->back().u != u || st->back().v != v)
				{
					st->pop_back();
					tmpComponent.push_back(st->back().u);
					tmpComponent.push_back(st->back().v);
				}
				tmpComponent.push_back(st->back().u);
				tmpComponent.push_back(st->back().v);
				vector <int>::iterator it = tmpComponent.begin();
				sort(tmpComponent.begin(), tmpComponent.end());
				it = unique(tmpComponent.begin(), tmpComponent.end());
				tmpComponent.erase(it, tmpComponent.end());
				componentSet.push_back(tmpComponent);
				tmpComponent.clear();

				st->pop_back();
				cnt++;
			}
		}

		else if (v != parent[u] && disc[v] < low[u])
		{
			low[u] = min(low[u], disc[v]);
			st->push_back(Edge(u, v));
		}
	}
}

void Graph::BCC()
{
	int *disc = new int[V];
	int *low = new int[V];
	int *parent = new int[V];
	list<Edge> *st = new list<Edge>[E];

	for (int i = 0; i < V; i++)
	{
		disc[i] = NIL;
		low[i] = NIL;
		parent[i] = NIL;
	}

	for (int i = 0; i < V; i++)
	{
		if (disc[i] == NIL)
			BCCUtil(i, disc, low, st, parent);

		int j = 0;

		while (st->size() > 0)
		{
			j = 1;
			tmpComponent.push_back(st->back().u);
			tmpComponent.push_back(st->back().v);
			st->pop_back();
		}
		if (j == 1)
		{
			cnt++;
			vector <int>::iterator it = tmpComponent.begin();
			sort(tmpComponent.begin(), tmpComponent.end());
			it = unique(tmpComponent.begin(), tmpComponent.end());
			tmpComponent.erase(it, tmpComponent.end());
			componentSet.push_back(tmpComponent);
			tmpComponent.clear();
		}
	}

}

void input(Graph &myGraph, FILE *fp) {
	for (int i = 0; i < N; i++) {
		int start;
		fscanf(fp, "%d", &start);
		int tmp;
		fscanf(fp, "%d", &tmp);
		while (tmp) {
			myGraph.addEdge(start, tmp);
			myGraph.addEdge(tmp, start);
			fscanf(fp, "%d", &tmp);
		}
	}
}

void sortComponent() {
	int size = componentSet.size();
	for (int i = 0; i < size; i++) {
		for (int j = i + 1; j < size; j++) {
			if (componentSet[i].size() < componentSet[j].size()) {
				vector <int> tmp;
				tmp = componentSet[i];
				componentSet[i] = componentSet[j];
				componentSet[j] = tmp;
			}
			else if (componentSet[i].size() == componentSet[j].size()) {
				int tmpSize = componentSet[i].size();
				for (int k = 0; k < tmpSize; k++) {
					if (componentSet[i][k] > componentSet[j][k]) {
						vector <int> tmp;
						tmp = componentSet[i];
						componentSet[i] = componentSet[j];
						componentSet[j] = tmp;
						break;
					}
					else if (componentSet[i][k] < componentSet[j][k])
						break;
					else
						continue;
				}
			}
		}
	}
}

void process(Graph &myGraph) {
	myGraph.BCC();
	sort(componentSet.begin(), componentSet.end());
	sortComponent();
}

void output() {
	FILE *fp = fopen("food.out", "w");
	resultComponent = componentSet[0];
	for (int i = 0; i < resultComponent.size(); i++) {
		fprintf(fp, "%d ", resultComponent[i]);
	}
	fclose(fp);
}

int main()
{
	FILE *fp_input = fopen("food.inp", "r");
	fscanf(fp_input, "%d", &N);
	Graph g(N + 1);

	input(g, fp_input);
	fclose(fp_input);
	process(g);
	output();

	return 0;
}