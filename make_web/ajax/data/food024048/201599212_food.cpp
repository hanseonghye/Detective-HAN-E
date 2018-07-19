// A C++ program to find biconnected components in a given undirected graph
// Geeks에서 찾는 코드로 실험
#include<iostream>
#include <list>
#include <stack>
#include <fstream>
#include <vector>
#include <algorithm>
#define NIL -1
using namespace std;
int cCnt = 0;
int N;

// 문제풀이용
int cmp_max_sz;
vector<vector<int> > cmp_set;
vector<int> trg_cmp;
void vector_push( vector<int>& v, int n ){
    for( int i=0; i<v.size(); ++i )
        if( v[i] == n ) return;
    v.push_back(n);
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
                    vector_push( cmp_set[cCnt], st->back().u+1);
                    vector_push( cmp_set[cCnt], st->back().v+1);
                    st->pop_back();
                }
                vector_push( cmp_set[cCnt], st->back().u+1);
                vector_push( cmp_set[cCnt], st->back().v+1);
                st->pop_back();
                cCnt++;
                cmp_set.push_back(vector<int>());
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
            vector_push( cmp_set[cCnt], st->back().u+1);
            vector_push( cmp_set[cCnt], st->back().v+1);
            st->pop_back();

        }
        if(j == 1)
        {
            cCnt++;
            cmp_set.push_back(vector<int>());
        }
    }
}
void vec_print( vector<int>& v, ostream& o ){
    for( int i=0; i<v.size(); ++i )
        o << v[i] << ' ';
}
bool vec_compare( vector<int>& s, vector<int>& d ){
    for( int i=0; i<s.size(); ++i )
        if( s[i] > d[i] ) return true;
        else if (s[i] <d[i] ) return false;
    return false;
}
// Driver program to test above function
int main(){
    ifstream rd("food.inp");
    ofstream pt("food.out");
    int src, dst, i, j;
    rd >> N;
    cmp_set.push_back(vector<int>());
    Graph g(N);
    for( int i=0; i<N; ++i ){
        rd >> src;
        while( (rd >> dst) && (dst != 0) ){
            g.addEdge(src-1, dst-1);
        }
    }
    g.BCC();

    for( i=0; i<cCnt; ++i ){
        sort(cmp_set[i].begin(), cmp_set[i].end());
        if( cmp_set[i].size() > cmp_max_sz )
            cmp_max_sz = cmp_set[i].size();
    }

    for( i=0; i<cCnt && cmp_set[i].size() != cmp_max_sz ; ++i );
    trg_cmp = cmp_set[i];
    for( j=0; j<cCnt; ++j ){
        if( cmp_set[j].size() == cmp_max_sz ){
            if( vec_compare(trg_cmp, cmp_set[j]) )
                trg_cmp = cmp_set[j];
        }
    }

    vec_print(trg_cmp, pt);
    pt.close();
    return 0;
}
