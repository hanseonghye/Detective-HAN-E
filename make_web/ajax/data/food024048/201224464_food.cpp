/** open source
* site	 : https://www.geeksforgeeks.org/biconnected-components/
* author : Anurag Singh
*/

#include<iostream>
#include<fstream>
#include<vector>
#include<algorithm>
#include <list>
#include <stack>
#define NIL -1
using namespace std;
int ccount = 0;
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
   	vector<int> result, bccStor;
   
    // A Recursive DFS based function used by BCC()
    void BCCUtil(int u, int disc[], int low[],
                 list<Edge> *st, int parent[]);
public:
    Graph(int V);   // Constructor
    void addEdge(int v, int w);   // function to add an edge to graph
    void BCC();    // prints strongly connected components
    void setResult(vector<int> v);
    void print(){
    	ofstream out("food.out");
    	for(int i=0; i < result.size(); i++){
    		out << result[i]+1 << " ";
		}
		out.close();
	}
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
   
void Graph::setResult(vector<int> v){
	if(result.size() < v.size()){
		result = v;
	}
	else if(result.size() == v.size()){
		for(int i = 0; i < result.size(); i++){
			if(result[i] < v[i]){
				break;
			}
			else if(result[i] > v[i]){
				result = v;
				break;
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
                    bccStor.push_back(st->back().u);
                    bccStor.push_back(st->back().v);
                    st->pop_back();
                }
                bccStor.push_back(u);
                bccStor.push_back(v);
                st->pop_back();
                //cout << endl;
                ccount++;
                sort(bccStor.begin(), bccStor.end());
    			bccStor.erase(unique(bccStor.begin(), bccStor.end()), bccStor.end());
    			setResult(bccStor);
				bccStor.clear();
            }
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
        //If stack is not empty, pop all edges from stack
        while(st->size() > 0)
        {
            j = 1;
            bccStor.push_back(st->back().u);
            bccStor.push_back(st->back().v);
            st->pop_back();
        }
        if(j == 1)
        {
            //cout << endl;
            ccount++;
            sort(bccStor.begin(), bccStor.end());
    		bccStor.erase(unique(bccStor.begin(), bccStor.end()), bccStor.end());
    		setResult(bccStor);
    		bccStor.clear();
        }
    }
}
  
// Driver program to test above function
int main()
{
	int V, fv, ffv;
	vector<int*> edgeMap;
	ifstream inp("food.inp");
	inp >> V;
	Graph g(V);

	while(!inp.eof()){
		inp >> fv;
		for(;;){
			inp >> ffv;
			if(ffv != 0){
				g.addEdge(fv-1, ffv-1);
			}
			else{
				break;
			}
		}
	}
    g.BCC();
    g.print();
	return 0;
}