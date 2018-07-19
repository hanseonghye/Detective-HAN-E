//  출저 :  https://www.geeksforgeeks.org/biconnected-components/

#include<iostream>
#include <list>
#include <stack>
#include <math.h>
#include <fstream>
#include <algorithm>
#include <vector>

#define NIL -1
using namespace std;
int count1 = 0;

vector <list<int> > li;

int li_count = 0;
bool comp(const list<int> &a, const list<int> &b) {
	if (a.size() != 0 && (a.size() == b.size()))
		return a.front() < b.front();
	return a.size() > b.size();
}
int min(int x, int y) {
	if (x < y) return x;
	else return y;
}
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

// A recursive function that finds and prints strongly connected
// components using DFS traversal
// u --> The vertex to be visited next
// disc[] --> Stores discovery times of visited vertices
// low[] -- >> earliest visited vertex (the vertex with minimum
//             discovery time) that can be reached from subtree
//             rooted with current vertex
// *st -- >> To store visited edges
void Graph::BCCUtil(int u, int disc[], int low[], list<Edge> *st,
	int parent[])
{
	// A static variable is used for simplicity, we can avoid use
	// of static variable by passing a pointer.
	static int time = 0;

	// Initialize discovery time and low value
	disc[u] = low[u] = ++time;
	int children = 0;

	// Go through all vertices adjacent to this
	list<int>::iterator i;

	for (i = adj[u].begin(); i != adj[u].end(); ++i)
	{
		int v = *i;  // v is current adjacent of 'u'

					 // If v is not visited yet, then recur for it
		if (disc[v] == -1)
		{

			children++;
			parent[v] = u;
			//store the edge in stack
			st->push_back(Edge(u, v));
			BCCUtil(v, disc, low, st, parent);

			// Check if the subtree rooted with 'v' has a
			// connection to one of the ancestors of 'u'
			// Case 1 -- per Strongly Connected Components Article
			low[u] = min(low[u], low[v]);

			//If u is an articulation point,
			//pop all edges from stack till u -- v
			if ((disc[u] == 1 && children > 1) ||
				(disc[u] > 1 && low[v] >= disc[u]))
			{
				while (st->back().u != u || st->back().v != v)
				{

					li[li_count].push_back(st->back().u);
					li[li_count].push_back(st->back().v);
					st->pop_back();
				}
				li[li_count].push_back(st->back().u);
				li[li_count].push_back(st->back().v);
				li[li_count].sort();
				li[li_count].unique();
				st->pop_back();
				count1++;
				li_count++;
			}
		}

		// Update low value of 'u' only of 'v' is still in stack
		// (i.e. it's a back edge, not cross edge).
		// Case 2 -- per Strongly Connected Components Article
		else if (v != parent[u] && disc[v] < low[u])
		{
			low[u] = min(low[u], disc[v]);
			st->push_back(Edge(u, v));
		}
	}
}

// The function to do DFS traversal. It uses BCCUtil()
void Graph::BCC()
{
	int *disc = new int[V];
	int *low = new int[V];
	int *parent = new int[V];
	list<Edge> *st = new list<Edge>[E];

	// Initialize disc and low, and parent arrays
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
		//If stack is not empty, pop all edges from stack
		while (st->size() > 0)
		{
			j = 1;

			st->pop_back();
		}
		if (j == 1)
		{

			count1++;
		}
	}
}

// Driver program to test above function
int main()
{
	int x, OO, temp = -1;//OO = 태초
	li.resize(100);
	ifstream fin;
	fin.open("food.inp");
	fin >> x;
	Graph g(x + 1);
	for (int i = 0; i < x; i++) {
		fin >> OO;
		while (1) {
			fin >> temp;
			if (temp == 0) break;
			g.addEdge(OO, temp);
		}
	}
	fin.close();
	g.BCC();

	sort(li.begin(), li.end(), comp);
	list<int> ::iterator it;

	ofstream fout;
	fout.open("food.out");

	for (it = li[0].begin(); it != li[0].end(); it++) {
		fout << *it << " ";
	}
	fout.close();
	return 0;
}