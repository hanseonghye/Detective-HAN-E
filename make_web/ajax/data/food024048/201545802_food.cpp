//------------------------------------------------------------------------
// http://www.geeksforgeeks.org/biconnected-components/
// author: Anurag Singh
// A C++ program to find biconnected components in a given undirected graph
#include <array>
#include <set>
#include <iostream>
#include <list>
#include <stack>
#define NIL -1
using namespace std;
int count = 0;
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
                 list<Edge> *st, int parent[],
                 array<set<int>,50>& ret_arr);
public:
    Graph(int V);   // Constructor
    void addEdge(int v, int w);   // function to add an edge to graph
    void BCC(array<set<int>,50>&);    // prints strongly connected components
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
static int bcc_label = 0;
void Graph::BCCUtil(int u, int disc[], int low[], list<Edge> *st,
                    int parent[], array<set<int>,50>& ret_arr)
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
            BCCUtil(v, disc, low, st, parent, ret_arr);
   
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
                    //cout << "[A]";
                    //cout << st->back().u << "--" << st->back().v << " ";
                        ret_arr[bcc_label].insert(st->back().u);
                        ret_arr[bcc_label].insert(st->back().v);
                    st->pop_back();
                }
                //cout << "[b]";
                //cout << st->back().u << "--" << st->back().v;
                        ret_arr[bcc_label].insert(st->back().u);
                        ret_arr[bcc_label].insert(st->back().v);
                st->pop_back();
                //cout << endl;
                count++;
                        //cout << bcc_label << endl;
                        bcc_label++;
            //cout << "------------------------------" << endl;
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
void Graph::BCC(array<set<int>,50>& ret_arr)
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
            BCCUtil(i, disc, low, st, parent, ret_arr);
          
        int j = 0;
        //If stack is not empty, pop all edges from stack
        while(st->size() > 0)
        {
            j = 1;
            //cout << st->back().u << "--" << st->back().v << " ";
                        ret_arr[bcc_label].insert(st->back().u);
                        ret_arr[bcc_label].insert(st->back().v);
            st->pop_back();
        }
        if(j == 1)
        {
            //cout << endl;
            count++;
        }
    }
}
//------------------------------------------------------------------------

#include <string>
#include <fstream>

#include <vector>
#include <utility>
#include <algorithm>

using std::vector;
using std::array;
using std::set;
using std::istream;
using std::ostream;
using std::string;

using std::cout;
using std::endl;
using std::sort;

set<int> result_bcc(array<set<int>,50>& bcc_arr)
{
    sort(bcc_arr.begin(), bcc_arr.end(),
        [](const set<int>& a, const set<int>& b){
            auto a_size = a.size();
            auto b_size = b.size();

            if(a_size == b_size)
                return (a < b); 
            return (a_size > b_size);
        }
    );
    return bcc_arr[0];
}

array<vector<int>,50> read_from(istream& input, int& vertex_num)
{
    int                     num;
    array<vector<int>,50>   arr;

    input >> num;
    for(int i = 0; i < num; i++){
        int vertex;
        do{
            input >> vertex;
            arr[i].push_back(vertex);
        }while(vertex != 0);
    }

    vertex_num = num;
    return arr;
}

void write_to(ostream& outstream, const set<int>& bcc)
{
    for(int vertex: bcc){
        outstream << vertex << ' ';
    }
}

array<set<int>,50> get_bcc_arr(const array<vector<int>,50>& data_arr)
{
    array<set<int>,50> ret_arr;
    bcc_label = 0;

    Graph g(100);
    for(int i = 0; i < 50; i++){
        const auto& vec = data_arr[i];
        int vec_size = vec.size();
        if(vec_size == 0)
            break;
        int edge_num = vec_size - 2; 
        int src_vertex = vec[0];
        for(int j = 1; j <= edge_num; j++){
            int dst_vertex = vec[j]; 
            //cout << src_vertex << ',' << dst_vertex << '|';
            g.addEdge(src_vertex, dst_vertex);
            //cout << src_vertex << ',' << dst_vertex << endl;
            g.addEdge(dst_vertex, src_vertex);
        }
    }

    // get biconnected_components
    g.BCC(ret_arr);

    return ret_arr;
}

int main(void){
    std::ifstream inp_stream("food.inp");
    std::ofstream out_stream("food.out");
    int n;
    auto data_arr = read_from(inp_stream, n);
    auto bcc_arr = get_bcc_arr(data_arr);
    auto bcc = result_bcc(bcc_arr);
    write_to(out_stream, bcc);
    return 0;
}
