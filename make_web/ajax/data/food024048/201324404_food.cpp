//√‚¿˙ https://www.geeksforgeeks.org/biconnected-components/
#include<iostream>
#include <list>
#include <stack>
#include <math.h>
#include <fstream>
#include <algorithm>
#include <vector>

#define NIL -1
using namespace std;
int counter = 0;

vector <list<int> > temp_list;
int temp_vertex, first_value;
int temp_counter = 0;


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
int min(int x, int y) {
	if (x < y) return x;
	else return y;
}

class Graph
{
	int V;   
	int E;   
	list<int> *adj; 
	void BCCUtil(int u, int disc[], int low[],
		list<Edge> *st, int parent[]);
public:
	Graph(int V);   
	void addEdge(int v, int w);
	void BCC();   
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

					temp_list[temp_counter].push_back(st->back().u);
					temp_list[temp_counter].push_back(st->back().v);
					st->pop_back();
				}


				temp_list[temp_counter].push_back(st->back().u);
				temp_list[temp_counter].push_back(st->back().v);
				temp_list[temp_counter].sort();
				temp_list[temp_counter].unique();
				st->pop_back();

				counter++;
				temp_counter++;
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

			st->pop_back();
		}
		if (j == 1)
		{

			counter++;
		}
	}
}
bool comp_list(const list<int> &data1, const list<int> &data2) {
	if (data1.size() != 0 && (data1.size() == data2.size()))
		return data1.front() < data2.front();

	return data1.size() > data2.size();
}

void process(){
	ifstream fin;
	fin.open("food.inp");

	temp_list.resize(100);

	int find_ver, first_value;

	int temp = -1;

	fin >> find_ver;

	Graph cut_ver(find_ver + 1);

	for (int i = 0; i < find_ver; i++) {
		fin >> first_value;
		while (1) {
			fin >> temp;
			if (temp == 0) break;
			cut_ver.addEdge(first_value, temp);
		}
	}

	cut_ver.BCC();

	sort(temp_list.begin(), temp_list.end(), comp_list);
}
void out() {
	ofstream fout;
	fout.open("food.out");

	list<int> ::iterator it;

	for (it = temp_list[0].begin(); it != temp_list[0].end(); it++) {
		fout << *it << " ";
	}

	fout.close();
}

int main()
{
	process();
	out();
	return 0;
}