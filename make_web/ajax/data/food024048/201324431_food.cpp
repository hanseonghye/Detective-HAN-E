//http://www.geeksforgeeks.org/articulation-points-or-cut-vertices-in-a-graph/  //geeksforgeeks에서 cut vertex코드 사용
#include<iostream>
#include <list>
#include <vector>
#include <fstream>
#include <algorithm>
#include <cstring>
#include <string>
#include <queue>
#include <functional>
#define NIL -1
using namespace std;

int vertexNum;

// A class that represents an undirected graph
class Graph
{
    int V;    // No. of vertices
    list<int> *adj;    // A dynamic array of adjacency lists
    void APUtil(int v, bool visited[], int disc[], int low[],
                int parent[], bool ap[]);
public:
    Graph(int V);   // Constructor
    void addEdge(int v, int w);   // function to add an edge to graph
    void AP();    // prints articulation points
};

Graph::Graph(int V)
{
    this->V = V;
    adj = new list<int>[V];

}

void Graph::addEdge(int v, int w)
{
    adj[v].push_back(w);// Note: the graph is undirected
}

// A recursive function that find articulation points using DFS traversal
// u --> The vertex to be visited next
// visited[] --> keeps tract of visited vertices
// disc[] --> Stores discovery times of visited vertices
// parent[] --> Stores parent vertices in DFS tree
// ap[] --> Store articulation points
void Graph::APUtil(int u, bool visited[], int disc[],
                                      int low[], int parent[], bool ap[])
{
    // A static variable is used for simplicity, we can avoid use of static
    // variable by passing a pointer.
    static int time = 0;

    // Count of children in DFS Tree
    int children = 0;

    // Mark the current node as visited
    visited[u] = true;

    // Initialize discovery time and low value
    disc[u] = low[u] = ++time;

    // Go through all vertices aadjacent to this
    list<int>::iterator i;
    for (i = adj[u].begin(); i != adj[u].end(); ++i)
    {
        int v = *i;  // v is current adjacent of u

        // If v is not visited yet, then make it a child of u
        // in DFS tree and recur for it
        if (!visited[v])
        {
            children++;
            parent[v] = u;
            APUtil(v, visited, disc, low, parent, ap);

            // Check if the subtree rooted with v has a connection to
            // one of the ancestors of u
            low[u]  = min(low[u], low[v]);

            // u is an articulation point in following cases

            // (1) u is root of DFS tree and has two or more chilren.
            if (parent[u] == NIL && children > 1)
               ap[u] = true;

            // (2) If u is not root and low value of one of its child is more
            // than discovery value of u.
            if (parent[u] != NIL && low[v] >= disc[u])
               ap[u] = true;
        }

        // Update low value of u for parent function calls.
        else if (v != parent[u])
            low[u]  = min(low[u], disc[v]);
    }
}

// The function to do DFS traversal. It uses recursive function APUtil()
void Graph::AP()
{
    // Mark all the vertices as not visited
    bool *visited = new bool[V];
    int *disc = new int[V];
    int *low = new int[V];
    int *parent = new int[V];
    bool *ap = new bool[V]; // To store articulation points

    // Initialize parent and visited, and ap(articulation point) arrays
    for (int i = 0; i < V; i++)
    {
        parent[i] = NIL;
        visited[i] = false;
        ap[i] = false;
    }

    // Call the recursive helper function to find articulation points
    // in DFS tree rooted with vertex 'i'
    for (int i = 0; i < V; i++) {
        if (visited[i] == false) {
            APUtil(i, visited, disc, low, parent, ap);
        }
    }

    vector<bool> isCutVertex(V, false);
    vector<bool> allIsVisit(V, false);
    vector<bool> thisIsVisit(V, false);
    vector<vector<int>> resultAll; //쏘팅후에 가장 긴 것 위치 여러개찾고 제일 위의 행을 +1해서 출력하면 답임
    vector<int> tempResult; //클리어 시키는것 잊지 말것
    queue<int> findVertexNeigh; //클리어 시키는것 잊지 말것
    int maxSubGraphNum = 0;

    // Now ap[] contains articulation points, print them
    for (int i = 0; i < V; i++) {
        if (ap[i] == true) {
            isCutVertex[i] = true;
            //cout << i << " ";
        }
    }
    //cout << endl;
    //cout << endl;

    /*list<int>::iterator j;
    for(int i = 0; i < V; i++) {
        for (j = adj[i].begin(); j != adj[i].end(); j++) {
            cout << *j << " ";
        }
        cout << endl;
    }*/

    for(int i = 0; i < V; i++) {
        if(isCutVertex[i] == false && allIsVisit[i] == false) {
            findVertexNeigh.push(i);

            while(1) {
                if(findVertexNeigh.empty()) {
                    break;
                } else {
                    int tempVertex = findVertexNeigh.front();
                    findVertexNeigh.pop();

                    if(thisIsVisit[tempVertex] == false) {
                        allIsVisit[tempVertex] = true;
                        thisIsVisit[tempVertex] = true;
                        tempResult.push_back(tempVertex);

                        list<int>::iterator k;
                        for (k = adj[tempVertex].begin(); k != adj[tempVertex].end(); k++) {

                            if(isCutVertex[*k] == true && thisIsVisit[*k] == false) {
                                tempResult.push_back(*k);
                                thisIsVisit[*k] = true;
                            } else if(isCutVertex[*k] == false && thisIsVisit[*k] == false) {
                                findVertexNeigh.push(*k);
                            }
                        }
                    }

                }
            }
            if(tempResult.size() > maxSubGraphNum) {
                maxSubGraphNum = tempResult.size();
            }

            sort(tempResult.begin(), tempResult.end());
            resultAll.push_back(tempResult);

            tempResult.clear();
            thisIsVisit.clear();
            for(int m = 0; m < V; m ++) {
                thisIsVisit.push_back(false);
            }
        }
    }

    //cout << "size:" << maxSubGraphNum << endl;

    int maxComponentLoc;
    sort(resultAll.begin(), resultAll.end());

    for(int i = 0; i < resultAll.size(); i ++) {
        if(resultAll[i].size() == maxSubGraphNum) {
            maxComponentLoc = i;
            break;
        }
    }

    ofstream outputFile;

	outputFile.open("food.out");


    for(int i = 0; i < resultAll[maxComponentLoc].size(); i++) {
        //cout << resultAll[maxComponentLoc][i] + 1 << " ";
        outputFile << resultAll[maxComponentLoc][i] + 1 << " ";
    }

    outputFile.close();

}

//output function
void outputFileResult() {

}

// Driver program to test above function
int main()
{
    freopen("food.inp", "r", stdin);

    cin >> vertexNum;
    Graph myGraph(vertexNum);

    int thisVertex;
    int nextVertex;

    for(int i = 0; i < vertexNum; i ++) {
        cin >> thisVertex;

        while(1) {
            cin >> nextVertex;
            if(nextVertex == 0) {
                break;
            } else {
                myGraph.addEdge(thisVertex - 1, nextVertex - 1);
            }
        }
    }

    myGraph.AP();

    outputFileResult();

    return 0;
}
