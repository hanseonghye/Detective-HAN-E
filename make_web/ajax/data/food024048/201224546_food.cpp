//√‚√≥ : https://www.geeksforgeeks.org/articulation-points-or-cut-vertices-in-a-graph/

//// A C++ program to find articulation points in an undirected graph
//#include<iostream>
//#include <vector>
//#include <algorithm>
//#include <fstream>
//#include <queue>
//#define NIL -1
//
//using namespace std;
//ifstream iFile;
//ofstream oFile;
//int min(int a, int b)
//{
//	return a > b ? b : a;
//}
//
//// A class that represents an undirected graph
//class Graph
//{
//	int V;    // No. of vertices
//	vector<int> *adj;    // A dynamic array of adjacency vectors
//	void APUtil(int v, bool visited[], int disc[], int low[],
//		int parent[], bool ap[]);
//public:
//	Graph(int V);   // Constructor
//	void addEdge(int v, int w);   // function to add an edge to graph
//	void AP(vector<int>& artiVertex);    // prints articulation points
//	void GetBiconnectedComponet(vector<int>*& biConnected, vector<int> artiVertex);
//	
//};
//
//void Graph::GetBiconnectedComponet(vector<int>*& biConnected, vector<int> artiVertex)
//{
//	bool** arr = new bool*[V];
//	for (int i = 0; i < V; i++)
//	{
//		arr[i] = new bool[V];
//		for (int j = 0; j < V; j++)
//		{
//			arr[i][j] = false;
//		}
//	}
//
//	int flag;
//	for (int i = 0; i < V; i++)
//	{
//		flag = 0;
//		
//		for (int j = 0; j < adj[i].size(); j++)
//		{
//			arr[i][adj[i][j]] = true;
//			arr[adj[i][j]][i] = true;
//		}
//		
//	}
//	for (int i = 0; i < V;i++)
//	{
//		for (int j = 0; j < artiVertex.size(); j++)
//		{
//			if (i == artiVertex[j])
//			{
//				for (int k = 0; k < V; k++)
//				{
//					arr[i][k] = false;
//					arr[k][i] = false;
//				}
//			}
//		}
//	}
//
//	vector<int>* temp = new vector<int>[V];
//	for (int i = 0; i < V; i++)
//	{
//		for (int j = 0; j < adj[i].size(); j++)
//		{
//			temp[i].push_back(adj[i][j]);
//		}
//	}
//
//
//	for (int i = 0; i < V; i++)
//	{
//		for (int j = 0; j < temp[i].size(); j++)
//		{
//			if (!arr[i][temp[i][j]])
//			{
//				temp[i][j] = -1;
//			}
//		}
//	}
//
//	for (int i = 0; i < V; i++)
//	{
//		cout << i << endl;
//		for (int j = 0; j < temp[i].size(); j++)
//		{
//				cout << temp[i][j] << ' ';
//			
//		}
//		cout << endl;
//	}
//
//	queue<int> que;
//	biConnected = new vector<int>[artiVertex.size() + 1];
//	for (int i = 0; i < artiVertex.size() + 1; i++)
//	{
//		for (int j = 0; j < V; j++)
//		{
//			int cnt = 0;
//			int a, b;
//			for (int k = 0; k < temp[j].size(); k++)
//			{
//				if (cnt == 0)
//				{
//					if (temp[j][k] != -1)
//					{
//						biConnected[i].push_back(temp[j][k]);
//						temp[j][k] = -1;
//						cnt++;
//					}
//				}
//
//			}
//		}
//		
//	}
//
//	/*biConnected = new vector<int>[artiVertex.size() + 1];
//
//	int index = 0;
//	int flag;
//	int flag2;
//	for (int i = 0; i < V;i++)
//	{
//		flag = 0;
//		for (vector<int>::iterator iter = adj[i].begin(); iter != adj[i].end(); iter++)
//		{
//			for (int j = 0; j < artiVertex.size(); j++)
//			{
//				if (artiVertex[j] == adj[i].front())
//				{
//					flag = 1;
//					break;
//				}
//			}
//			if (flag == 1)
//				break;
//		}
//		if (flag == 1)
//			continue;
//		for (vector<int>::iterator iter = adj[i].begin(); iter != adj[i].end(); iter++)
//		{
//			flag2 = 0;
//			for (int j = 0; j < artiVertex.size(); j++)
//			{
//				if (artiVertex[j] == *iter)
//				{
//					flag2 = 1;
//					break;
//				}
//			}
//			if (flag2 == 0)
//			{
//				biConnected[index].push_back(*iter);
//			}
//		}
//		index++;
//	}
//	for (int i = 0; i < index;i++)
//	{
//		for (int j = 0; j < biConnected[i].size(); j++)
//			cout << biConnected[i][j] << ' ';
//		cout << endl;
//	}*/
//}
//
//Graph::Graph(int V)
//{
//	this->V = V;
//	adj = new vector<int>[V];
//}
//
//void Graph::addEdge(int v, int w)
//{
//	adj[v].push_back(w);
//	//adj[w].push_back(v);  // Note: the graph is undirected
//}
//
//// A recursive function that find articulation points using DFS traversal
//// u --> The vertex to be visited next
//// visited[] --> keeps tract of visited vertices
//// disc[] --> Stores discovery times of visited vertices
//// parent[] --> Stores parent vertices in DFS tree
//// ap[] --> Store articulation points
//void Graph::APUtil(int u, bool visited[], int disc[],
//	int low[], int parent[], bool ap[])
//{
//	// A static variable is used for simplicity, we can avoid use of static
//	// variable by passing a pointer.
//	static int time = 0;
//
//	// Count of children in DFS Tree
//	int children = 0;
//
//	// Mark the current node as visited
//	visited[u] = true;
//
//	// Initialize discovery time and low value
//	disc[u] = low[u] = ++time;
//
//	// Go through all vertices aadjacent to this
//	vector<int>::iterator i;
//	for (i = adj[u].begin(); i != adj[u].end(); ++i)
//	{
//		int v = *i;  // v is current adjacent of u
//
//					 // If v is not visited yet, then make it a child of u
//					 // in DFS tree and recur for it
//		if (!visited[v])
//		{
//			children++;
//			parent[v] = u;
//			APUtil(v, visited, disc, low, parent, ap);
//
//			// Check if the subtree rooted with v has a connection to
//			// one of the ancestors of u
//			low[u] = min(low[u], low[v]);
//
//			// u is an articulation point in following cases
//
//			// (1) u is root of DFS tree and has two or more chilren.
//			if (parent[u] == NIL && children > 1)
//				ap[u] = true;
//
//			// (2) If u is not root and low value of one of its child is more
//			// than discovery value of u.
//			if (parent[u] != NIL && low[v] >= disc[u])
//				ap[u] = true;
//		}
//
//		// Update low value of u for parent function calls.
//		else if (v != parent[u])
//			low[u] = min(low[u], disc[v]);
//	}
//}
//
//// The function to do DFS traversal. It uses recursive function APUtil()
//void Graph::AP(vector<int>& artiVertex)
//{
//	// Mark all the vertices as not visited
//	bool *visited = new bool[V];
//	int *disc = new int[V];
//	int *low = new int[V];
//	int *parent = new int[V];
//	bool *ap = new bool[V]; // To store articulation points
//
//							// Initialize parent and visited, and ap(articulation point) arrays
//	for (int i = 0; i < V; i++)
//	{
//		parent[i] = NIL;
//		visited[i] = false;
//		ap[i] = false;
//	}
//
//	// Call the recursive helper function to find articulation points
//	// in DFS tree rooted with vertex 'i'
//	for (int i = 0; i < V; i++)
//		if (visited[i] == false)
//			APUtil(i, visited, disc, low, parent, ap);
//
//	// Now ap[] contains articulation points, print them
//	for (int i = 0; i < V; i++)
//		if (ap[i] == true)
//			artiVertex.push_back(i);
//}
//
//// Driver program to test above function
//int main()
//{
//	iFile.open("1.inp", ios::in);
//	oFile.open("food.out", ios::out);
//
//	int N;
//	iFile >> N;
//	Graph g(N);
//	
//	for (int i = 0; i < N; i++)
//	{
//		int firstNum;
//		iFile >> firstNum;
//		while (1)
//		{
//			int num;
//			iFile >> num;
//			
//			if (num == 0)
//				break;
//			g.addEdge(firstNum - 1, num - 1);
//		}
//	}
//
//	
//
//
//	vector<int> artiVertex;
//	g.AP(artiVertex);
//	for (int i = 0; i < artiVertex.size(); i++)
//	{
//		cout << artiVertex[i] << ' ';
//	}
//	cout << endl << endl;
//	
//
//	
//	vector<int>* biConnectedComponent;
//	g.GetBiconnectedComponet(biConnectedComponent, artiVertex);
//
//	/*for (int i = 0;i < artiVertex.size() + 1; i++)
//	{
//		for (int j = 0; j < biConnectedComponent[i].size(); j++)
//		{
//			cout << biConnectedComponent[i][j] << ' ' ;
//		}
//		cout << endl;
//	}*/
//	
//
//	return 0;
//}


#include<iostream>
#include <list>
#include <stack>
#include <vector>
#include <fstream>
#include <algorithm>
#define NIL -1
using namespace std;
int cnt = 0;
vector<int> bcc[50];
ifstream iFile;
ofstream oFile;


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

int min(int a, int b)
{
	return a > b ? b : a;
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
					int a = st->back().u;
					int b = st->back().v;
					bcc[cnt].push_back(a);
					bcc[cnt].push_back(b);
					
					//cout << st->back().u << "--" << st->back().v << " ";
					st->pop_back();
				}
				int a = st->back().u;
				int b = st->back().v;
				bcc[cnt].push_back(a);
				bcc[cnt].push_back(b);
				
				//cout << st->back().u << "--" << st->back().v;
				st->pop_back();
				cnt++;
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
			int a = st->back().u;
			int b = st->back().v;
			bcc[cnt].push_back(a);
			bcc[cnt].push_back(b);
			
			//cout << st->back().u << "--" << st->back().v << " ";
			st->pop_back();
		}
		if (j == 1)
		{
			cnt++;
		}
	}
}

int findMin(vector<int> v)
{
	int min = v[0];
	for (int i = 1; i < v.size(); i++)
	{
		if (min > v[i])
			min = v[i];
	}
	return min;
}

// Driver program to test above function
int main()
{
	iFile.open("food.inp", ios::in);
	oFile.open("food.out", ios::out);

	int N;
	iFile >> N;
	Graph g(N);

	for (int i = 0; i < N; i++)
	{
		int firstNum;
		iFile >> firstNum;
		while (1)
		{
			int num;
			iFile >> num;

			if (num == 0)
				break;
			g.addEdge(firstNum - 1, num - 1);
		}
	}
	g.BCC();

	for (int i = 0; i < cnt; i++)
	{
		sort(bcc[i].begin(), bcc[i].end());
	}

	for (int i = 0; i < cnt; i++)
	{
		for (int j = 0; j < bcc[i].size() - 1; j++)
		{
			for(int k = j + 1 ; k<bcc[i].size(); k++)
			if (bcc[i][j] == bcc[i][k])
				bcc[i][k] = -1;
		}
	}

	int count, beforeCount = 0;;
	int index;
	for (int i = 0; i < cnt; i++)
	{
		count = 0;
		for (int j = 0; j < bcc[i].size(); j++)
		{
			if (bcc[i][j] != -1)
			{
				count++;
			}	
		}
		if (beforeCount < count)
		{
			beforeCount = count;
			index = i;
		}
		else if (beforeCount == count)
		{
			beforeCount = count;
			if (bcc[index][0] > bcc[i][0])
				index = i;
		}
	}

	for (int i = 0; i < bcc[index].size(); i++)
	{
		if (bcc[index][i] != -1)
		{
			oFile << bcc[index][i] + 1 << ' ';
			cout << bcc[index][i] + 1 << ' ';
		}
	}
	return 0;
}
