#include <bits/stdc++.h>
#define MAX_N 50
using namespace std;
int n, m, disc[MAX_N+1], cut[MAX_N+1], d, M_dep;
vector<vector<int>> adj(51),path_set,result;
vector<int> path,cut_set;
int Visited[51],detect[51];
int dfs(int here, bool r) {
    disc[here] = ++d;
    int ret = disc[here];
    int child = 0;
    for (int there : adj[here]) {
        if (!disc[there]) {
            child++;
            int df = dfs(there, 0);
            if (!r&&df >= disc[here])
                cut[here] = true;
            ret = min(ret, df);
        }
        else
            ret = min(ret, disc[there]);
    }
    if (r&&child > 1)
        cut[here] = true;
    return ret;
}
void dfs_find(int cur){
    Visited[cur] = 1;
    path.push_back(cur);
    for(int i = 0; i < adj[cur].size(); ++i){
        int there = adj[cur][i];
        if(cut[there]&&detect[there] == 0){
            cut_set.push_back(there);
            detect[there] = 1;
        }
        if(!Visited[there]&&!cut[there])
            dfs_find(there);
    }
}
int main() {
    ifstream fin;
    ofstream fout;
    fin.open("food.inp");
    fout.open("food.out");
    fin >> n;
    adj.resize(n + 1);
    for (int i = 0; i < n; ++i) {
        int x,y;
        fin >> x;
        while(1){
            fin >> y;
            if(y == 0)
                break;
            adj[x].push_back(y);
        }
    }
    for (int i = 1; i <= n; ++i)
        if (!disc[i])
            dfs(i, 1);//단절점 찾고
    for(int i = 1; i <= n; ++i){
        if(!Visited[i] && !cut[i]){
            dfs_find(i);//단절점 제거 한 그래프들을 dfs탐색
            memset(detect,0,sizeof(detect));
            path.insert(path.end(),cut_set.begin(),cut_set.end());
            sort(path.begin(),path.end());
            path_set.push_back(path);
            path.clear();
            cut_set.clear();
        }
    }
    for(int i = 0; i < path_set.size(); ++i){
        if(M_dep <= path_set[i].size()){
            M_dep = path_set[i].size();
        }
    }
    for(int i = 0; i < path_set.size(); ++i){
        if(M_dep == path_set[i].size())
            result.push_back(path_set[i]);
    }
    sort(result.begin(),result.end());
    for(int i = 0; i < result[0].size(); ++i){
        fout << result[0][i] << ' ';
    }
    fin.close();
    fout.close();
    return 0;
}
//단절점 찾은 상태에서 단절점을 다 끊고 생각했다. 그 끊은 그래프들을 dfs탐색하고 탐색 도중 인접노드가 단절점이면
//dfs를 탐색했던 노드들이 있는 path에 단절점들을 추가하고 그러면 그 집합은 biconnected graph가 된다는것을 깨달았다.
//단절점 찾기 open source 활용
//출처: http://jason9319.tistory.com/119 [ACM-ICPC 상 탈 사람]
