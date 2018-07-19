/*
*
*   reference site : http://www.geeksforgeeks.org/biconnected-components/
*
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <stack>
#define NIL -1
using namespace std;
int cnt = 0;


ifstream input;
ofstream output;
vector<int> result;
unsigned int maximum = 0;

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
	vector<int> *adj;    // A dynamic array of adjacency lists

						 // A Recursive DFS based function used by BCC()
	void BCCUtil(int u, int disc[], int low[], vector<Edge> *st, int parent[]);
public:
	Graph(int V);   // Constructor
	void addEdge(int v, int w);   // function to add an edge to graph
	void BCC();    // prints strongly connected components
	void input_graph(int num);
	void hasCheck(vector<int> *tmp, vector<Edge> *st);
	void isMax(vector<int> tmp);

};

Graph::Graph(int V)
{
	this->V = V;
	this->E = 0;
	adj = new vector<int>[V];
}

void Graph::addEdge(int v, int w)
{
	adj[v].push_back(w);
	E++;
}



void Graph::input_graph(int num)
{
	int before = 0;
	for (int i = 0; i < num; i++) {
		while (true) {
			int tmp;
			input >> tmp;
			if (before == 0) {
				before = tmp;
				continue;
			}
			if (tmp == 0) {
				before = tmp;
				break;
			}
			else {
				addEdge(before, tmp);
			}
		}
	}
}

// A recursive function that finds and prints strongly connected
// components using DFS traversal
// u --> The vertex to be visited next
// disc[] --> Stores discovery times of visited vertices
// low[] -- >> earliest visited vertex (the vertex with minimum
//             discovery time) that can be reached from subtree
//             rooted with current vertex
// *st -- >> To store visited edges
void Graph::BCCUtil(int u, int disc[], int low[], vector<Edge> *st,
	int parent[])
{
	// A static variable is used for simplicity, we can avoid use
	// of static variable by passing a pointer.
	static int time = 0;

	// Initialize discovery time and low value
	disc[u] = low[u] = ++time;
	int children = 0;

	// Go through all vertices adjacent to this
	vector<int> tmp;
	vector<int>::iterator i;
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
				tmp.clear();
				while (st->back().u != u || st->back().v != v)
				{
					hasCheck(&tmp, st);

					//cout << st->back().u << "--" << st->back().v << " ";
					st->pop_back();
				}

				hasCheck(&tmp, st);
				//cout << st->back().u << "--" << st->back().v;
				st->pop_back();
				cnt++;

				sort(tmp.begin(), tmp.end());
				isMax(tmp);
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
	vector<Edge> *st = new vector<Edge>[E];

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
			//cout << st->back().u << "--" << st->back().v << " ";
			st->pop_back();
		}
		if (j == 1)
		{
			cout << endl;
			cnt++;
		}
	}
}

void Graph::hasCheck(vector<int> *tmp, vector<Edge> *st)
{
	bool hasU = false;
	bool hasV = false;
	vector<int>::iterator i;

	for (i=tmp->begin(); i != tmp->end(); i++) {
		if (*i == st->back().u)
			hasU = true;

	}
	if (!hasU)
		tmp->push_back(st->back().u);

	for (i = tmp->begin(); i != tmp->end(); i++) {
		if (*i == st->back().v)
			hasV = true;
	}
	if (!hasV)
		tmp->push_back(st->back().v);

}

void Graph::isMax(vector<int> tmp)
{
	vector<int>::iterator i;

	if (tmp.size() > maximum) {
		result.clear();
		for (i=tmp.begin(); i != tmp.end(); i++) {
			result.push_back(*i);
		}
		maximum = result.size();
	}
	else if (tmp.size() == result.size()) {
		for (int i = 0; i < tmp.size(); i++) {
			if (tmp.at(i) > result.at(i))
				break;
			else if (tmp.at(i) == result.at(i))
				continue;
			else {
				result.clear();
				for (int j = 0; j < tmp.size(); j++) {
					result.push_back(tmp.at(j));
				}
				break;
			}

		}
	}
}
int main()
{
	int num;
	vector<int>::iterator i;
	input.open("food.inp");
	output.open("food.out");

	input >> num;
	Graph g(num + 1);
	g.input_graph(num);

	g.BCC();
	for (i = result.begin(); i != result.end(); i++)
		output << *i << " ";

	return 0;

}