#include <iostream>
#include <fstream>
#include <algorithm>
#include <map>
#include <stack>
#include <vector>

using namespace std;
struct fnode
{
    fnode() { parent=-1, reachPoint=-1, stackOrder=0, visited=false;}
    int parent;
    int reachPoint, stackOrder;
    bool visited;
    vector < int > child;
};
typedef struct fnode fnode;
typedef pair < int, int > pType;

typedef map < int, fnode > mfType;
vector < vector < pType > > TComponent;
stack < pType > edgeStack;
stack < int > stackDFS;
mfType fdata;

void file_read();
void findBicomponents();
void dfs(int findex);
vector <int> findThebestGraph();
/* optional::method */
void setBiconnectedGraph(int p, int v);
int minBystack(int a, int b);
int getElementbyStack(int a);
bool judge(vector <int>& a, vector <int>& b);
/* optional::print */
void print_res(vector <int>& t);
void print_subgraph(vector < pType >& v);
void print_rp();
void print_vector(vector <int> & a);
void print_edge(stack < pType > e);
int main()
{
    file_read();
    findBicomponents();
    vector <int> res=findThebestGraph();
    print_res(res);
    return 0;
}
void file_read()
{
    int key, size, n;
    ifstream ifs("food.inp");
    ifs >> size;
    while(size-- > 0)
    {
        fnode temp;
        ifs >> key;
        while(ifs >> n)
        {
            if(n != 0)
            {
                temp.child.push_back(n);
            }
            else break;
        }
        sort(temp.child.begin(), temp.child.end());
        fdata.insert(make_pair(key, temp));
    }
}
void findBicomponents()
{
    //cout << " --- search DFS --- " << endl;
    mfType::iterator it=fdata.begin();
    for(; it != fdata.end(); ++it)
    {
        int key=(*it).first;
        bool isVisted=(*it).second.visited;
        if(!isVisted) { dfs(key);}

    }
    //cout << " --- done DFS --- " << endl;
}
void dfs(int u)
{
    static int stackOrder = 0;
    fdata[u].visited=true;
    fdata[u].stackOrder=stackOrder++;
    fdata[u].reachPoint=u;
    vector < int >::iterator it=fdata[u].child.begin();
    //cout << "\n --- dfs : " << u << " --- " << endl;
    for(; it < fdata[u].child.end(); ++it)
    {
        int v=(*it);
        //print_edge(edgeStack);
        if(!fdata[v].visited)
        {
            edgeStack.push(make_pair(u, v));
            //cout << " > " << u << " -> " << v << endl;
            fdata[v].parent=u;
            dfs(v);
            //cout << " > visit : " << v << endl;
            int vp=fdata[v].reachPoint;
            //cout << "child(" << v << ") reachPoint :" << vp << ", its stackOrder :" << fdata[vp].stackOrder << endl;
            //cout << "parent(" << u << ") stackOrder :" << fdata[u].stackOrder << endl;
            if(fdata[vp].stackOrder >= fdata[u].stackOrder) { setBiconnectedGraph(u, v);}
            fdata[u].reachPoint=minBystack(fdata[u].reachPoint, fdata[v].reachPoint);
            //cout << " > " << u << "is reached at :" << fdata[u].reachPoint << endl;
        }
        else if(fdata[u].parent != v && fdata[v].stackOrder < fdata[u].stackOrder)
        {
            //backEdge found
            edgeStack.push(make_pair(u, v));
            //cout << " > backedge : " << u << " -> " << v << endl;
            int up=fdata[u].reachPoint;
            int us=fdata[up].stackOrder, vs=fdata[v].stackOrder;
            //cout << " > parent :" << u << endl;
            //cout << " > then it reached :" << fdata[u].reachPoint << ", cur_child :" << v << endl;
            fdata[u].reachPoint=us < vs? up : v;
            //cout << " > cur_parent_reach :" << fdata[u].reachPoint << endl;
            //print_rp();
        }
    }
}
/* optional::method */
int minBystack(int a, int b)
{
  //ret;urn reachPoint
  return fdata[a].stackOrder < fdata[b].stackOrder? a : b;
}
void setBiconnectedGraph(int u, int v)
{
    //cout << "\n --- Find component --- " << endl;
    pType target=make_pair(u, v);
    int i=TComponent.size();
    TComponent.push_back(vector < pType >());
    //cout << " >> target :" << '(' << u << ", " << v << ")" << endl;
    //cout << " >>init_top :" << e.first << ", " << e.second << endl;
    while(edgeStack.top() != target)
    {
          //cout << "-";
          pType e=edgeStack.top();
          edgeStack.pop();
          TComponent[i].push_back(e);
    }
    pType eTop=edgeStack.top();
    //cout << " >> edgeTop :" << eTop.first << ", " << eTop.second << endl;
    edgeStack.pop();
    TComponent[i].push_back(eTop);
    //cout << " --- done Find component --- " << endl;
    //print_subgraph(TComponent[i]);
}
int getElementbyStack(int _stackNum)
{
    mfType::iterator it_begin=fdata.begin();
    mfType::iterator it_end=fdata.end();

    for(; it_begin != it_end; ++it_begin)
    {
        if((*it_begin).second.stackOrder == _stackNum) { return (*it_begin).first;}
    }
    return -1;
}
vector <int> rearrage(vector < pType >& src)
{
    vector <int> val;
    vector <pType>::iterator it=src.begin();
    vector <pType>::iterator it_end=src.end();
    for(; it != it_end; ++it)
    {
        val.push_back((*it).first);
        val.push_back((*it).second);
    }
    sort(val.begin(), val.end());
    vector <int>::iterator dup=unique(val.begin(), val.end());
    val.erase(dup, val.end());
    return val;
}
vector <int> findThebestGraph()
{
    //cout << " --- findThebestGraph --- " << endl;
    //cout << " >> extract vertex " << endl;
    vector < vector < pType > >::iterator it=TComponent.begin();
    vector < vector < pType > >::iterator it_end=TComponent.end();
    map < int, vector < int > > vertexOfgraph;
    int res=0;
    for(; it != it_end; ++it)
    {
        vector <int> val=rearrage((*it));
        int key=val.size();
        if(vertexOfgraph.find(key) == vertexOfgraph.end())
        {   //no duplication
            vertexOfgraph.insert(make_pair(key, val));
        }
        else
        {   //detect same size
            //cout << " same key is input !!! " << endl;
            //cout << "key :" << key << endl;
            //print_vector(val);
            if(!judge(vertexOfgraph[key], val))
            {
                vertexOfgraph[key].clear();
                vertexOfgraph[key]=val;
            }
            //print_vector(grapVertex[key]);
        }
        if(res < key)
          res=key;
    }
    //cout << " >> RESULT " << endl;
    return vertexOfgraph[res];
}
bool judge(vector <int>& a, vector <int>& b)
{
    //false -> change
    for(unsigned i=0; i<a.size(); ++i)
    {
        //cout << a[i] << " - " << b[i] << endl;
        if(a[i] > b[i]) {return false;}
        else if(a[i] == b[i]) {;}
        else {return true;}//if(a[i] < b[i])
    }
    return true;
}
/* optional::print */
void print_res(vector <int>& t)
{
    ofstream ofs("food.out");
    vector < int >::iterator it=t.begin();
    for(; it !=t.end(); ++it)
    {
        ofs << (*it) << ' ';
    }
    ofs.close();
}
void print_subgraph(vector < pType >& v)
{
    //cout << "\n --- print bitconnected subgraph --- " << endl;
    vector < pType >::iterator it_begin=v.begin();
    vector < pType >::iterator it_end=v.end();
    for(; it_begin != it_end; ++it_begin)
    {
        //cout << '(' << (*it_begin).first << ", " << (*it_begin).second << ")" << endl;
    }
}
void print_rp()
{
    //cout << " --- check reachPoint --- " << endl;
    mfType::iterator it_begin=fdata.begin();
    mfType::iterator it_end=fdata.end();
    for(; it_begin != it_end; ++it_begin)
    {
        cout << '(' << (*it_begin).first << "):";
        cout << (*it_begin).second.reachPoint << endl;
    }
    cout << endl;
}
void print_vector(vector <int> & a)
{
    vector <int>::iterator it=a.begin();
    vector <int>::iterator it_end=a.end();
    for(; it != it_end; ++it)
    {
        cout << *it << ' ';
    }
    cout << endl;
}
void print_edge(stack < pType > e)
{
    cout << "\n --- print edgeStack --- " << endl;
    while(!e.empty())
    {
        pType element = e.top();
        e.pop();
        cout << '(' << element.first << ", " << element.second << ")" << endl;
    }
}
