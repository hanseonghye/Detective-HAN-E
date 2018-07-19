/* http://www.geeksforgeeks.org/biconnected-components/
    를 참고 했습니다 ! */


#include <iostream>
#include <list>
#include <stack>
#include <fstream>
#include <iterator>
#include <set>
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

set<set <int> > my_list;
int max_size=0;
set<int> result;


void Graph::BCCUtil(int u, int disc[], int low[], list<Edge> *st,
                    int parent[])
{
    static int time = 0;
    disc[u] = low[u] = ++time;
    int children = 0;
    list<int>::iterator i;
    for (i = adj[u].begin(); i != adj[u].end(); ++i)
    {
        int v = *i;

        if (disc[v] == -1)
        {
            children++;
            parent[v] = u;

            st->push_back(Edge(u,v));
            BCCUtil(v, disc, low, st, parent);
            low[u]  = min(low[u], low[v]);

            if( (disc[u] == 1 && children > 1) ||
                (disc[u] > 1 && low[v] >= disc[u]) )
            {
                set <int> temp;
                set <int>::iterator it=temp.begin();
                while(st->back().u != u || st->back().v != v)
                {
                    temp.insert(st->back().u);
                    temp.insert(st->back().v);
                 //   cout << st->back().u <<" "<< "--" << st->back().v << " ";
                    st->pop_back();
                }
                temp.insert(st->back().u);
                temp.insert(st->back().v);
                my_list.insert(temp);
              //  cout << st->back().u << "--" <<st->back().v;
                st->pop_back();
                count++;

                if( max_size < temp.size() ){
                    max_size=temp.size();
                    result=temp;
                }
                else if( max_size == temp.size() ){
                    set<int>::iterator iter1=temp.begin(), iter2=result.begin();
                    while(1){
                        if(*iter1==*iter2) { ++iter1; ++iter2; }
                        else if(*iter1<*iter2) { result=temp; break; }
                        else { break; }
                    }

                }


            }


        }

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

    int max_size=0;

    // Initialize disc and low, and parent arrays
    for (int i = 0; i < V; i++)
    {
        disc[i] = NIL;
        low[i] = NIL;
        parent[i] = NIL;
    }

    for (int i = 0; i < V; i++)
        BCCUtil(i, disc, low, st, parent);

}

// Driver program to test above function
int main()
{
    int n;
    ifstream fin;
    ofstream fout;
    fin.open("food.inp");
    fout.open("food.out");
    fin>>n;
    Graph g(n+1);

    for(int i=0;i<n;++i){
        int num1; fin>>num1;
        
        while(1){
            int num2; fin>>num2;
            if(num2==0) break;
            g.addEdge(num1,num2);
        }
    }

    g.BCC();
    set <int>::iterator it2;
    for(it2=result.begin();it2!=result.end();it2++)
        fout<<*it2<<" ";

    return 0;
}
