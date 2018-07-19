//오픈 소스 출처 : https://www.geeksforgeeks.org/biconnected-components/


#include <fstream>
#include <list>
#include <stack>
#include <vector>
#include <algorithm>
#define NIL -1

using namespace std;

vector<int> max_comp;

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


void find_max_comp(vector<int>& v)
{
	if(max_comp.size()<v.size())
		max_comp.swap(v);
	else if(max_comp.size()==v.size()) {
		int i;
		for(i=0;i<max_comp.size() && max_comp[i]>v[i];++i)
			;
		if(i<max_comp.size())
			max_comp.swap(v);
	}
}

void bi_comp(list<Edge> *st, vector<int>& v) {
	int a1 = st->back().u+1, a2 = st->back().v+1;
	if(find(v.begin(),v.end(),a1)==v.end())
		v.push_back(a1);
	if(find(v.begin(),v.end(),a2)==v.end())
		v.push_back(a2);
	st->pop_back();
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

			st->push_back(Edge(u,v));
			BCCUtil(v, disc, low, st, parent);

			low[u] = min(low[u], low[v]);
			
			if( (disc[u] == 1 && children > 1) || (disc[u] > 1 && low[v] >= disc[u]) )
			{
				vector<int> a;
				while(st->back().u != u || st->back().v != v)
					bi_comp(st,a);
				bi_comp(st,a);
				sort(a.begin(), a.end());
				find_max_comp(a);
			}
		}
		else if(v != parent[u] && disc[v] < low[u])
		{
			low[u] = min(low[u], disc[v]);
			st->push_back(Edge(u,v));
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
		vector<int> a;
		while(st->size() > 0)
		{
			bi_comp(st,a);
		}
		sort(a.begin(), a.end());
		find_max_comp(a);
	}
}

int main()
{
	ifstream ifs("food.inp");
	ofstream ofs("food.out");
	int n;
	ifs >> n;
	Graph g(n);
	for(int i=0;i<n;++i) {
		int v,k;
		ifs >> v >> k;
		while(k!=0) {
			g.addEdge(v-1,k-1);
			ifs >> k;
		}
	}
	g.BCC();
	for(int i=0;i<max_comp.size();++i)
		ofs << max_comp[i] << ' ';
	ifs.close();
	ofs.close();
	return 0;
}

