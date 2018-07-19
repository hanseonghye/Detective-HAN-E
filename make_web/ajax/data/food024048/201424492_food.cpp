// using https://nbangla.blogspot.kr/2012/12/cpp-articulation-bridge-detection-algorithm.html?m=1
// using https://www.geeksforgeeks.org/bridge-in-a-graph/
// using https://www.geeksforgeeks.org/connected-components-in-an-undirected-graph/
#include <fstream>
#include <algorithm>
#include <iostream>
#include <list>
#include <vector>
#include <set>
#define NIL -1
using namespace std;

ifstream in("food.inp");
ofstream out("food.out");

class Graph
{
	int V;    
	int MaxNumOfComponetsVertexs;
	
	list<int> *adj;   
	set<int> MaxComponet;
	set<int> MaxComponetCandidate;

	vector<pair<int, int>> bridges;
	vector<int> APs; // Articulation point - graph를 자르는 Vertex

	void bridgeUtil(int v, bool visited[], int disc[], int low[],
		int parent[]);
	void APDFS(int v, bool visited[], int disc[], int low[],
		int parent[], bool ap[]);
	void ComponetsDFS(int v, bool visited[]);
	bool IsNotArticulationPoint(int &v);
public:
	Graph(int V);   
	void addEdge(int v, int w);  
	void RemoveEdge(int v, int w);   
	void RemoveEdges();
	void Bridge();   
	void AP();
	void RemoveAPpathes(int v);
	void CutBetweenAPs();
	void ConnectedComponents();
	void OutMaxComponet();

};

Graph::Graph(int V)
{
	this->V = V;
	adj = new list<int>[V];

	MaxNumOfComponetsVertexs = 0;
}

void Graph::addEdge(int v, int w)
{
	adj[v].push_back(w);
	adj[w].push_back(v);  
}

void Graph::RemoveEdge(int v, int w)
{
	adj[v].remove(w);
	adj[w].remove(v);  
}

void Graph::RemoveEdges()
{
	for (std::vector<pair<int, int>>::iterator it = bridges.begin(); it != bridges.end(); ++it)
	{
		//out << "removed edge:" << it->first << " " << it->second << endl;
		RemoveEdge(it->first, it->second);
	}
}

void Graph::bridgeUtil(int u, bool visited[], int disc[],
	int low[], int parent[])
{
	static int time = 0;
	visited[u] = true;

	disc[u] = low[u] = ++time;

	list<int>::iterator i;
	for (i = adj[u].begin(); i != adj[u].end(); ++i)
	{
		int v = *i;
		if (!visited[v])
		{
			parent[v] = u;
			bridgeUtil(v, visited, disc, low, parent);

			low[u] = min(low[u], low[v]);

			if (low[v] > disc[u])
				bridges.push_back(make_pair(u, v));
		}
		else if (v != parent[u])
			low[u] = min(low[u], disc[v]);
	}
}


void Graph::Bridge()
{
	bool *visited = new bool[V];
	int *disc = new int[V];
	int *low = new int[V];
	int *parent = new int[V];

	for (int i = 0; i < V; i++)
	{
		parent[i] = NIL;
		visited[i] = false;
	}

	for (int i = 0; i < V; i++)
		if (visited[i] == false)
			bridgeUtil(i, visited, disc, low, parent);
}


void Graph::AP()
{
	bool *visited = new bool[V];
	int *disc = new int[V];
	int *low = new int[V];
	int *parent = new int[V];
	bool *ap = new bool[V]; 

	for (int i = 1; i < V; i++)
	{
		parent[i] = NIL;
		visited[i] = false;
		ap[i] = false;
	}
	for (int i = 1; i < V; i++)
		if (visited[i] == false)
			APDFS(i, visited, disc, low, parent, ap);

	for (int i = 1; i < V; i++)
		if (ap[i] == true)
			APs.push_back(i);
}

void Graph::APDFS(int u, bool visited[], int disc[],
	int low[], int parent[], bool ap[])
{

	static int time = 0;
	int children = 0;

	visited[u] = true;

	disc[u] = low[u] = ++time;

	list<int>::iterator i;
	for (i = adj[u].begin(); i != adj[u].end(); ++i)
	{
		int v = *i;
		if (!visited[v])
		{
			children++;
			parent[v] = u;
			APDFS(v, visited, disc, low, parent, ap);
			low[u] = min(low[u], low[v]);

			if (parent[u] == NIL && children > 1)
				ap[u] = true;

			if (parent[u] != NIL && low[v] >= disc[u])
				ap[u] = true;
		}

		else if (v != parent[u])
			low[u] = min(low[u], disc[v]);
	}
}


void Graph::RemoveAPpathes(int v)
{
	list<int>::iterator it;
	for (it = adj[v].begin(); it != adj[v].end();)
	{
		if (IsNotArticulationPoint(v))
		{
			it = adj[v].erase(it);  // 경로 제거
		}
		else
		{
			it++;
		}
	}
}

void Graph::CutBetweenAPs()
{
	for (std::vector<int>::iterator it = APs.begin(); it != APs.end(); ++it)
		RemoveAPpathes(*it);
}

void Graph::ConnectedComponents()
{
	bool *visited = new bool[V + 1];
	for (int v = 1; v < V; v++)
		visited[v] = false;

	for (int v = 1; v< V; v++)
	{
		if (visited[v] == false && IsNotArticulationPoint(v))
		{
			ComponetsDFS(v, visited);

			if (MaxComponetCandidate.size()> MaxNumOfComponetsVertexs) {
				MaxNumOfComponetsVertexs = MaxComponetCandidate.size();
				MaxComponet.swap(MaxComponetCandidate);
			}
		}

		MaxComponetCandidate.clear();
	}
}

void Graph::ComponetsDFS(int v, bool visited[])
{
	if (find(APs.begin(), APs.end(), v) == APs.end())
		visited[v] = true;
	MaxComponetCandidate.insert(v);


	list<int>::iterator i;
	for (i = adj[v].begin(); i != adj[v].end(); ++i)
	{
		if (!visited[*i] && IsNotArticulationPoint(v))
			ComponetsDFS(*i, visited);
	}
}

void Graph::OutMaxComponet()
{
	for (set<int>::iterator it = MaxComponet.begin(); it != MaxComponet.end(); ++it)
		out << *it << ' ';
}


bool Graph::IsNotArticulationPoint(int &v)
{
	return find(APs.begin(), APs.end(), v) == APs.end();
}


int main()
{
	int nVertex;
	int Vi, Vj;
	in >> nVertex;
	Graph g(nVertex + 1);
	for (int i = 0; i < nVertex; i++)
	{
		in >> Vi;
		while (in >> Vj && Vj != 0)
			g.addEdge(Vi, Vj);
	}
	g.Bridge();      // 브릿지 찾기
	g.RemoveEdges(); // 브릿지 제거하기
	g.AP();          // Articulation Point 찾기
	g.CutBetweenAPs();   // Articulation Point 를 기준으로 commponet나누기
	g.ConnectedComponents(); // Component 저장하기
	g.OutMaxComponet();

	in.close();
	out.close();
}