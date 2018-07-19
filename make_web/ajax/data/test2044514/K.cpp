#include <bits/stdc++.h>
using namespace std;
typedef pair<int,int> pii;
const int INF =1e9;
int mx=-INF,n,v[55][55],par[55],d[55],vis[55];
int bv[55][55];
pii ansd;
void dfs(int hr){
	vis[hr]=1;
	for(int nxt=1;nxt<=n;++nxt){
		if(hr!=nxt && v[hr][nxt]<=10000&&!vis[nxt]){
			dfs(nxt);
		}
	}
}
void bellmanford(int s){
	int update =1;
	for(int i=1;i<=n;++i)d[i]=INF;
	d[s]=0;
	for(int s =0;s<n;++s){
		update = 0;
		for(int j=1;j<=n;++j){
			for(int k =1;k<=n;++k){
				if(d[k]>bv[j][k]+d[j]){
					d[k]=d[j]+bv[j][k];
					par[k]=j;
					update=1;
				}
			}
		}
		if(!update)break;
	}
}

int main(){
	freopen("eleccar.inp","r",stdin);
	freopen("eleccar.out","w",stdout);
	cin>>n;
	for(int i=1;i<=n;++i){
		for(int j=1;j<=n;++j){
			cin>>v[i][j];
			if(v[i][j]==99999)v[i][j]=INF;
			bv[i][j]=v[i][j];
		}
	}
	for(int i=1;i<=n;++i){
		memset(vis,0,sizeof(vis));
		dfs(i);
		for(int j=1;j<=n;++j){
			if(!vis[j]){
				cout<<"99999";
				return 0;
			}
		}
	}
	for(int k=1;k<=n;++k){
		for(int i=1;i<=n;++i){
			for(int j=1;j<=n;++j){
				v[i][j]=min(v[i][j],v[i][k]+v[k][j]);
			}
		}
	}
	for(int k=1;k<=n;++k){
		for(int i=1;i<=n;++i){
			for(int j=1;j<=n;++j){
				if(i<j&&mx<v[i][j]){
					mx=v[i][j];
					ansd=pii(i,j);
				}
				if(v[i][j]>v[i][k]+v[k][j]){
					cout<<"nega-cycle";
					return 0;
				}
			}
		}
	}
	bellmanford(ansd.first);
	vector<int>ans;
	
	for(int i=ansd.second;i!=ansd.first;){
		ans.push_back(i);
		i=par[i];
	}
	cout<<mx<<endl;
	cout<<ansd.first<<' ';
	for(int i=ans.size()-1;i>=0;--i){
		cout<<ans[i]<<' ';
	}
	
}
