/*
Reference Site : http://www.geeksforgeeks.org/biconnected-components/
*/

// A C++ program to find biconnected components in a given undirected graph
#include<iostream>
#include <fstream>
#include <list>
#include <stack>
#include <algorithm>

#define NIL -1
using namespace std;
int myCount;
// Driver program to test above function
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
	bool *max_array;
	int max_lenght = 0;
	int min_first = 9999;
	// A Recursive DFS based function used by BCC()
	void BCCUtil(int u, int disc[], int low[],
		list<Edge> *st, int parent[]);
public:
	Graph(int V);   // Constructor
	void addEdge(int v, int w);   // function to add an edge to graph
	void BCC(ofstream *os);    // prints strongly connected components
};

Graph::Graph(int V)
{
	this->V = V;
	this->E = 0;
	adj = new list<int>[V];
	max_array = new bool[1];
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

	bool *temp_array;
	// Go through all vertices adjacent to this
	list<int>::iterator i;
	for (i = adj[u].begin(); i != adj[u].end(); ++i)
	{
		int v = *i;  // v is current adjacent of 'u'
		int len = 0, first = 9999;
		temp_array = new bool[V];
		fill_n(temp_array, V, false);
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
					//cout << st->back().u << "--" << st->back().v << " ";
					if (!temp_array[st->back().u]) {
						temp_array[st->back().u] = true;
						len++;
					}
					if (!temp_array[st->back().v]) {
						temp_array[st->back().v] = true;
						len++;
					}
					st->pop_back();
				}
				//cout << st->back().u << "--" << st->back().v;
				if (!temp_array[st->back().u]) {
					temp_array[st->back().u] = true;
					len++;
					if (first > st->back().u) {
						first = st->back().u;
					}
				}
				if (!temp_array[st->back().v]) {
					temp_array[st->back().v] = true;
					len++;
					if (first >st->back().v ) {
						first = st->back().v;
					}
				}
				st->pop_back();

				if (max_lenght < len) {
					free(max_array);
					max_array = temp_array;
					max_lenght = len;
				}
				else if (max_lenght == len) {
					if (min_first > first) {
						free(max_array);
						max_array = temp_array;
						min_first = first;
					}
				}

				//cout << endl;
				myCount++;
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
void Graph::BCC(ofstream*os)
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

	bool *temp_array;

	for (int i = 0; i < V; i++)
	{
		if (disc[i] == NIL)
			BCCUtil(i, disc, low, st, parent);

		int j = 0, len = 0,first=9999;
		//If stack is not empty, pop all edges from stack
		temp_array = new bool[V];
		fill_n(temp_array, V, false);
		while (st->size() > 0)
		{
			//j = 1;
			if (!temp_array[st->back().u]) {
				temp_array[st->back().u] = true;
				len++;
				if (first >  st->back().u) {
					first = st->back().u;
				}
			}
			if (!temp_array[st->back().v]) {
				temp_array[st->back().v] = true;
				len++;
				if (first > st->back().v) {
					first = st->back().v;
				}
			}
			//cout << st->back().u << "--" << st->back().v << " ";
			st->pop_back();
		}

		/*if (j == 1)
		{
		cout << endl;
		myCount++;
		}*/

		if (max_lenght < len) {
			free(max_array);
			max_array = temp_array;
			max_lenght = len;
		}
		else if (max_lenght == len) {
			if (min_first > first) {
				free(max_array);
				max_array = temp_array;
				min_first = first;
			}
		}
	}

	for (int i = 0; i < V; i++) {
		if (max_array[i])
			*os << i+1 << " ";
	}
}

int main()
{
	ifstream in("food.inp");
	ofstream out("food.out");
	int nodeNum,start,end;
	in >> nodeNum;
	
	Graph g(nodeNum);
	for (int i = 0; i < nodeNum; i++) {
		in >> start;
		in >> end;
		while (end != 0) {
			g.addEdge(start-1, end-1);
			in >> end;
		}
	}
	
	g.BCC(&out);

	in.close();
	out.close();
	return 0;
}