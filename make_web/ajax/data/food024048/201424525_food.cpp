/* ------- REFERENCE INFORMATION --------
SITE: http://www.geeksforgeeks.org/biconnected-components/
AUTHOR: Anurag Singh
*/

// A C++ program to find biconnected components in a given undirected graph
#include <iostream>
#include <fstream> 
#include <list>
#include <stack>
#include <set>
#include <vector>
#include <functional>
#define NIL -1
using namespace std;

int count = 0;

set<int> temp_component;
set<int> biggest_component;
set<int>::iterator iter, iter1, iter2;

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
            st->push_back(Edge(u,v));
            BCCUtil(v, disc, low, st, parent);
   
            // Check if the subtree rooted with 'v' has a
            // connection to one of the ancestors of 'u'
            // Case 1 -- per Strongly Connected Components Article
            low[u]  = min(low[u], low[v]);
  
            //If u is an articulation point,
            //pop all edges from stack till u -- v
            if( (disc[u] == 1 && children > 1) ||
                (disc[u] > 1 && low[v] >= disc[u]) )
            {
                while(st->back().u != u || st->back().v != v)
                {
                	int _u = st->back().u;
                	int _v = st->back().v;
                	/* -------- FOR CHECK -------- */
                    // cout << _u << "--" << _v << " ";
                    temp_component.insert(_u);
                    temp_component.insert(_v);
                    st->pop_back();
                }
                int _u = st->back().u;
                int _v = st->back().v;
                /* -------- FOR CHECK -------- */
                // cout << _u << "--" << _v;
                temp_component.insert(_u);
                temp_component.insert(_v);
                st->pop_back();
                /* -------- FOR CHECK -------- */
				// cout << endl;
                count++;
            }  
            /* -------- FOR CHECK -------- */
	        // cout << "size of temp_component: " << temp_component.size() << endl;
	        
	        /* -------- 2-CONNECTED-COMPONENT ---------*/
	   		if (biggest_component.size() == 0) { // biggest가 없으면 무조건 초기화 
	   			for (iter=temp_component.begin(); iter!=temp_component.end(); ++iter)
					biggest_component.insert(*iter);
			}
			if (temp_component.size() > biggest_component.size()) { // temp가 biggest보다 크면 갱신 
				biggest_component.clear();
				for (iter=temp_component.begin(); iter!=temp_component.end(); ++iter)
					biggest_component.insert(*iter);
			}
			else if (temp_component.size() == biggest_component.size()) { // temp와 biggest 크기가 같다면 사전순으로 빠른 녀석으로 갱신 
				// 사전순으로 누가 빠르나 검사
				iter1=temp_component.begin();
				iter2=biggest_component.begin();
				while (iter1 != temp_component.end() && iter2 != biggest_component.end() && *iter1 == *iter2) {
					++iter1, ++iter2;
				} 
				if (iter1 != temp_component.end() && iter2 != biggest_component.end()) {
					if (*iter1 < *iter2) { // temp가 사전순으로 더 빠르다면 갱신 
						biggest_component.clear();
						for (iter=temp_component.begin(); iter!=temp_component.end(); ++iter)
							biggest_component.insert(*iter);
					}
				}
			}
			temp_component.clear();
	    }
   
        // Update low value of 'u' only of 'v' is still in stack
        // (i.e. it's a back edge, not cross edge).
        // Case 2 -- per Strongly Connected Components Article
        else if(v != parent[u] && disc[v] < low[u])
        {
            low[u]  = min(low[u], disc[v]);
            st->push_back(Edge(u,v));
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
        // If stack is not empty, pop all edges from stack
        while(st->size() > 0)
        {
            j = 1;
            int _u = st->back().u;
            int _v = st->back().v;
            /* -------- FOR CHECK -------- */
            // cout << _u << "--" << _v << " ";
            temp_component.insert(_u);
			temp_component.insert(_v);
            st->pop_back();
            
            /* -------- 2-CONNECTED-COMPONENT ---------*/
	   		if (biggest_component.size() == 0) { // biggest가 없으면 무조건 초기화 
	   			for (iter=temp_component.begin(); iter!=temp_component.end(); ++iter)
					biggest_component.insert(*iter);
			}
			if (temp_component.size() > biggest_component.size()) { // temp가 biggest보다 크면 갱신 
				biggest_component.clear();
				for (iter=temp_component.begin(); iter!=temp_component.end(); ++iter)
					biggest_component.insert(*iter);
			}
			else if (temp_component.size() == biggest_component.size()) { // temp와 biggest 크기가 같다면 사전순으로 빠른 녀석으로 갱신 
				// 사전순으로 누가 빠르나 검사
				iter1=temp_component.begin();
				iter2=biggest_component.begin();
				while (iter1 != temp_component.end() && iter2 != biggest_component.end() && *iter1 == *iter2) {
					++iter1, ++iter2;
				} 
				if (iter1 != temp_component.end() && iter2 != biggest_component.end()) {
					if (*iter1 < *iter2) { // temp가 사전순으로 더 빠르다면 갱신 
						biggest_component.clear();
						for (iter=temp_component.begin(); iter!=temp_component.end(); ++iter)
							biggest_component.insert(*iter);
					}
				}
			}
			temp_component.clear();
        }
        if(j == 1)
        {
        	/* -------- FOR CHECK -------- */
        	// cout << endl;
            count++;
        }
    }
}
  
// Driver program to test above function
int main()
{    
	/* -------- READ INPUT FILE ---------- */
	ifstream in("food.inp");
	int num_of_vertex = 0, vertex1 = 0, vertex2 = 0;
	if (in.is_open()) {
		in >> num_of_vertex;
	}
	
	Graph g(num_of_vertex+1);
	for (int i=0; i<num_of_vertex; ++i) {
		in >> vertex1;
		in >> vertex2;
		while (vertex2 != 0) {
			/* -------- FOR CHECK -------- */
			// cout << "vertex1: " << vertex1 << " vertex2: " << vertex2 << endl;
			g.addEdge(vertex1, vertex2);
			in >> vertex2;
		}
	}
	in.close();
    
    g.BCC();
    // cout << "Above are " << count << " biconnected components in graph" << endl;
    
    /* -------- FOR CHECK -------- */
    /*
    cout << endl << "result: ";
	for (iter=biggest_component.begin(); iter!=biggest_component.end(); ++iter)
		cout << *iter << " ";
	cout << endl;
	*/
	
	/* -------- WRITE OUTPUT FILE ---------- */
	ofstream out("food.out");
	for (iter=biggest_component.begin(); iter!=biggest_component.end(); ++iter)
		out << *iter << " ";
	out.close();
	
	return 0;
}
