/*
https://www.geeksforgeeks.org/biconnected-components/
*/
#include<iostream>
#include <list>
#include <stack>
#include <math.h>
#include <fstream>
#include <algorithm>
#include <vector>

#define NIL -1

using namespace std;

int index = 0;

vector <list<int> > foodlist;

int food_index = 0;

void infile();
void outfile();

int main(){
	infile();
 	outfile();
   	return 0;
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
int min(int x, int y) {
   if (x < y) return x;
   else return y;
}

class Graph
{
   int V;   
   int E;   
   list<int> *adj; 
   void BCCUtil(int u, int disc[], int low[],
      list<Edge> *st, int parent[]);
public:
   Graph(int V);   
   void addEdge(int v, int w);
   void BCC();   
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
      
         st->push_back(Edge(u, v));
         BCCUtil(v, disc, low, st, parent);

         low[u] = min(low[u], low[v]);

         if ((disc[u] == 1 && children > 1) ||
            (disc[u] > 1 && low[v] >= disc[u]))
         {
            while (st->back().u != u || st->back().v != v){
               foodlist[food_index].push_back(st->back().u);
               foodlist[food_index].push_back(st->back().v);
               st->pop_back();
            }
            foodlist[food_index].push_back(st->back().u);
            foodlist[food_index].push_back(st->back().v);
            foodlist[food_index].sort();
            foodlist[food_index].unique();
            
			st->pop_back();

            index++;
            food_index++;
         }
      }

      else if (v != parent[u] && disc[v] < low[u])
      {
         low[u] = min(low[u], disc[v]);
         st->push_back(Edge(u, v));
      }
   }
}

void Graph::BCC()
{
   int *disc = new int[V];
   int *low = new int[V];
   int *parent = new int[V];
   list<Edge> *st = new list<Edge>[E];

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
      while (st->size() > 0)
      {
         j = 1;

         st->pop_back();
      }
      if (j == 1)
      {

         index++;
      }
   }
}

bool compare(const list<int> &comp1, const list<int> &comp2) {
   if (comp1.size() != 0 && (comp1.size() == comp2.size()))
      return comp1.front() < comp2.front();

   return comp1.size() > comp2.size();
}

void infile() {
	ifstream inf;
   if (inf == NULL){
        cout << "file is not exist.";
    }
	else{
   	inf.open("food.inp");
   
   	foodlist.resize(100);
   	int x, first_value;
   	int temp = -1;
   	inf >> x;

   	Graph g(x + 1);
   	for (int i = 0; i < x; i++) {
      	inf >> first_value;
      	while (1) {
        inf >> temp;
        if (temp == 0) break;
        g.addEdge(first_value, temp);
      	}
   	}

	g.BCC();
   	sort(foodlist.begin(), foodlist.end(), compare);
	}
}

void outfile() {
	list<int> ::iterator it;

   	ofstream fout;
   	fout.open("food.out");

   	for (it = foodlist[0].begin(); it != foodlist[0].end(); it++) {
      fout << *it << " ";
   	}
   	fout.close();
}
