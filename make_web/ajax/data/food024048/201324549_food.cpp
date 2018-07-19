#include <iostream>
#include <fstream>
#include <algorithm>
#include <stack>
#include <vector>
#define NIL -1

using namespace std;


int num = 0;
vector<int> foodvt;
unsigned int maxnum = 0;
int num_vertex;
ifstream fin("food.inp");


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

class Graph
{
   int V;
   int E;
   vector<int> *adj;

   void BCCUtil(int u, int disc[], int low[], vector<Edge> *vct, int high[]);
public:
   Graph(int V);
   void addEdge(int v, int w);
   void BCC();
   void file_input(int num);
   void file_output(vector<int> foodvt);
   void hasCheck(vector<int> *tmp, vector<Edge> *vct);
   void find_max(vector<int> tmp);


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


void Graph::BCCUtil(int u, int disc[], int low[], vector<Edge> *vct,
   int high[])
{
	   
   vector<int> tmp;
   static int time = 0;
   disc[u] = low[u] = ++time;
   int children = 0;

   vector<int>::iterator i;
   for (i = adj[u].begin(); i != adj[u].end(); ++i)
   {
      int v = *i; 

      if (disc[v] == -1)
      {
         children++;
         high[v] = u;
         vct->push_back(Edge(u, v));
         BCCUtil(v, disc, low, vct, high);
         
         low[u] = min(low[u], low[v]);

         if ((disc[u] == 1 && children > 1) ||
            (disc[u] > 1 && low[v] >= disc[u]))
         {
            tmp.clear();
            while (vct->back().u != u || vct->back().v != v)
            {
               hasCheck(&tmp, vct);
               vct->pop_back();
            }
            hasCheck(&tmp, vct);
            vct->pop_back();
            num++;

            sort(tmp.begin(), tmp.end());
            find_max(tmp);
         }
      }
      else if (v != high[u] && disc[v] < low[u])
      {
         low[u] = min(low[u], disc[v]);
         vct->push_back(Edge(u, v));
      }
   }
}

void Graph::BCC()
{
   int *disc = new int[V];
   int *low = new int[V];
   int *high = new int[V];
   vector<Edge> *vct = new vector<Edge>[E];

   for (int i = 0; i < V; i++)
   {
      disc[i] = NIL;
      low[i] = NIL;
      high[i] = NIL;
   }

   for (int i = 0; i < V; i++)
   {
      if (disc[i] == NIL)
         BCCUtil(i, disc, low, vct, high);

      int j = 0;

      while (vct->size() > 0)
      {
         j = 1;

         vct->pop_back();
      }
      if (j == 1)
      {
         cout << endl;
         num++;
      }
   }
}

void Graph::hasCheck(vector<int> *tmp, vector<Edge> *vct)
{
   bool hasU = false;
   bool hasV = false;
   vector<int>::iterator i;

   for (i=tmp->begin(); i != tmp->end(); i++) {
      if (*i == vct->back().u)
         hasU = true;

   }
   if (!hasU)
      tmp->push_back(vct->back().u);

   for (i = tmp->begin(); i != tmp->end(); i++) {
      if (*i == vct->back().v)
         hasV = true;
   }
   if (!hasV)
      tmp->push_back(vct->back().v);

}

void Graph::find_max(vector<int> tmp)
{
   vector<int>::iterator i;

   if (tmp.size() > maxnum) {
      foodvt.clear();
      for (i=tmp.begin(); i != tmp.end(); i++) {
         foodvt.push_back(*i);
      }
      maxnum = foodvt.size();
   }
   else if (tmp.size() == foodvt.size()) {
      for (int i = 0; i < tmp.size(); i++) {
         if (tmp.at(i) > foodvt.at(i))
            break;
         else if (tmp.at(i) == foodvt.at(i))
            continue;
         else {
            foodvt.clear();
            for (int j = 0; j < tmp.size(); j++) {
               foodvt.push_back(tmp.at(j));
            }
            break;
         }

      }
   }
}


void Graph::file_input(int num)
{

   int before = 0;
   for (int i = 0; i < num; i++) {
      while (true) {
         int tmp;
         fin >> tmp;
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

void Graph::file_output(vector<int> foodvt){
	ofstream fout("food.out");
	vector<int>::iterator i;
	for (i = foodvt.begin(); i != foodvt.end(); i++){
		fout << *i << " ";
	}
} 


int main()
{
	fin >> num_vertex;
	Graph g(num_vertex + 1);
	g.file_input(num_vertex);
	g.BCC();
	g.file_output(foodvt);

	return 0;
}
