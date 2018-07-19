#include <fstream>
#include <iostream>
#include <algorithm>
#include <vector>
#include <list>
#include <stack>
#define NIL -1
using namespace std;
/*https://www.geeksforgeeks.org/biconnected-components/ ÂüÁ¶*/

class Edge{
    public:
    int u;
    int v;
    Edge(int u, int v);
};
// A class that represents an directed graph
class Graph{
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
    void shownode();
};
//Declear global variable & function for subject
Graph readfile();
void writefile();
int N = 0;          //number of vertex
bool graph_sort(vector<int> a, vector<int> b);
vector<int> temp;
vector<vector<int> > Graph_List;

////////////////////////////////////////////////////////////////
Edge::Edge(int u, int v){
    this->u = u;
    this->v = v;
}

Graph::Graph(int V){
    this->V = V;
    this->E = 0;
    adj = new list<int>[V];
}

void Graph::addEdge(int v, int w){
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
void Graph::BCCUtil(int u, int disc[], int low[], list<Edge> *st, int parent[]){
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
                    temp.push_back(st->back().u);
                    temp.push_back(st->back().v);
                    st->pop_back();

                }
                temp.push_back(st->back().u);
                temp.push_back(st->back().v);
                st->pop_back();
                sort(temp.begin(),temp.end());
                temp.erase(unique(temp.begin(),temp.end()),temp.end());
                Graph_List.push_back(temp);
                temp.clear();
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
void Graph::BCC(){
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
            temp.push_back(st->back().u);
            temp.push_back(st->back().v);
            st->pop_back();
        }
        if(j == 1)
        {
            sort(temp.begin(),temp.end());
            temp.erase(unique(temp.begin(),temp.end()),temp.end());
            Graph_List.push_back(temp);
            temp.clear();
        }
    }
}

void Graph::shownode(){
    cout << "/////////////////////////////////////////////////////////" << endl;
    for(int i = 0 ; i < V ; i++){
        cout << i + 1 << " ";
        for(list<int>::iterator j = adj[i].begin() ; j != adj[i].end() ; j++){
            cout << *j + 1 << " ";
        }
        cout << endl;
    }
    cout << "/////////////////////////////////////////////////////////" << endl;
}

////////////////////////////////////////////////////////////////

int main(){
    Graph food = readfile();
    food.BCC();
    writefile();
}

Graph readfile(){
    ifstream read;
    int node, edge;
    read.open("food.inp");
    read >> N;
    Graph food(N);
    for(int i =  1; i <= N ; i++){
        read >> node;
        while(1){
            read >> edge;
            if(edge == 0){
                break;
            }
                food.addEdge(node-1, edge-1);
        }
    }
    read.close();
    return food;
}

void writefile(){
    ofstream write;
    write.open("food.out");
    sort(Graph_List.begin(),Graph_List.end(),graph_sort);
    for(int i = 0 ; i < Graph_List.front().size() ; i++){
        write << Graph_List.front()[i]+1 << " ";
    }
    write.close();
}

bool graph_sort(vector<int> a, vector<int> b){
    if(a.size() > b.size()){
        return true;
    }
    else if(a.size() < b.size()){
        return false;
    }
    else{
        if(a[0]>b[0]){
            return false;
        }
        else{
            return true;
        }
    }
}


