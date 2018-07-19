// 참고 자료: http://jason9319.tistory.com/119
#include <bits/stdc++.h>

using namespace std;

int n,d,disc[51],cut[51],chk[51],chk2[51],depth;
vector<int> cuts,path;
vector<vector<int> > gra,ans,paths;

void input(void){
	ifstream fin;
	fin.open("food.inp");
	fin >> n;
	gra.resize(n+1);
	for(int i=0; i<n; i++){
		int temp, temp_2;
		fin >> temp;
		while(1){
			fin >> temp_2;
			if(temp_2 == 0)
				break;
			gra[temp].push_back(temp_2);
		}
	}
	fin.close();
}

int dfs(int here, bool r) {
    disc[here] = ++d;
    int ret = disc[here];
    int child = 0;
    for (int there : gra[here]) {
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

void dfs2(int now){
    chk[now] = 1;
    path.push_back(now);
    for(int i=0; i < gra[now].size(); ++i){
        int there = gra[now][i];
        if(cut[there] && chk2[there]==0){
            cuts.push_back(there);
            chk2[there] = 1;
        }
        if(!chk[there] && !cut[there])
            dfs2(there);
    }
}

void output(void){
	ofstream fout;
	fout.open("food.out");
	for(int i=0; i<paths.size(); ++i){
        if(depth <= paths[i].size())
            depth = paths[i].size();
    }
    for(int i=0; i<paths.size(); ++i){
        if(depth == paths[i].size())
            ans.push_back(paths[i]);
    }
    sort(ans.begin(),ans.end());
	for(int i=0; i<ans[0].size(); ++i){
        fout << ans[0][i] << ' ';
    }
	fout.close();
}

int main(void) {
	input();
	
	for(int i=1; i<=n; ++i)
        if (!disc[i])
            dfs(i, 1);
    for(int i=1; i<=n; ++i){
        if(!chk[i] && !cut[i]){
            dfs2(i);
            memset(chk2,0,sizeof(chk2));
            path.insert(path.end(),cuts.begin(),cuts.end());
            sort(path.begin(),path.end());
            paths.push_back(path);
            path.clear();
            cuts.clear();
        }
    }
	output();
	return 0;
} 
