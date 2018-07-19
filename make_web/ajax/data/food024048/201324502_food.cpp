#include <bits/stdc++.h>
#define clean() tmp.clear(), memset(visited, false, sizeof(visited));

using namespace std;

int N, u, v, size;
vector<int> ans, tmp, adj[51];
bool visited[51], cutVertex[51], flag = false;

void dfs(int u){
    visited[u] = true;
    tmp.push_back(u);
    if(cutVertex[u] && flag) return;
    for(int v = 0; v < adj[u].size(); v++)
        if(!visited[adj[u][v]]) dfs(adj[u][v]);
}

int main()
{
    ifstream fin("food.inp");
    ofstream fout("food.out");
    fin >> N;
    for(int i = 0; i < N; i++){
        fin >> u;
        while(fin >> v){
            if(!v) break;
            adj[u].push_back(v);
        }
    }
    for(int i = 1; i <= N; i++){
        dfs(i);
        size = tmp.size() - 1;
        clean();
        visited[i] = true;
        dfs(adj[i][0]);
        if(tmp.size() != size) cutVertex[i] = true;
        clean();
    }
    flag = true;
    for(int i = 1; i <= N; i++){
        if(cutVertex[i]) continue;
        dfs(i);
        sort(tmp.begin(), tmp.end());
        if(tmp.size() > ans.size() || (tmp.size() == ans.size() && ans > tmp)) ans = tmp;
        clean();
    }
    for(int i = 0; i < ans.size(); i++) fout << ans[i] << " ";

    return 0;
}
