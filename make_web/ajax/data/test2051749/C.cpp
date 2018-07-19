#include <iostream>
#include <vector>
#include <string>
#include <stack>
#include <fstream>
#include <algorithm>
using namespace std;


stack<int>save;
vector<vector<pair<int,int>>> arr;
int dist_max;
int main(){
	
	int test,kind;
	int flag=0;
	ifstream fin;
	ofstream fout;
	fin.open("eleccar.inp");
	fout.open("eleccar.out");
	fin>>test;
	arr.resize(test+1);
	while(dist_max==0){
		for(int i=0;i<test;i++){
			for(int j=0;j<test;j++){
				int temp;
				fin>>temp;
				if(temp==0 || temp==99999)
					kind=-1;
				else
					kind=i;
				arr[i].push_back(make_pair(temp,kind));
			}
		}
		for(int k=0;k<test;k++){
			for(int i=0;i<test;i++){
				for(int j=0;j<test;j++){
					if(arr[i][j].first>arr[i][k].first+arr[k][j].first){
						arr[i][j].first=arr[i][k].first+arr[k][j].first;
						arr[i][j].second=arr[k][j].second;
					}
				}
			}
		}
		for(int i=0;i<test;i++){

			int cnt=0;
			for(int j=0;j<test;j++){
				if(arr[i][j].second==-1)
					cnt++;
				if((i==j) && arr[i][j].second != -1){
					dist_max=-99999;
					break;
				}
			}
			if(cnt==test){
				flag=1;
				break;
			}
		}
		if(dist_max==-99999){
			fout<<"nega-cycle";
			break;
		}
		if(flag==1){
			fout<<"99999";
			break;
		}
		for(int i=0;i<test;i++){
			for(int j=0;j<test;j++){
				if(i<j)
					dist_max=max(dist_max,arr[i][j].first);
			}
		}
		fout<<dist_max<<endl;
		for(int i=0;i<test;i++){
			for(int j=0;j<test;j++){
				if(dist_max==arr[i][j].first){
					int ans=j;
					save.push(j+1);
					while(i!=arr[i][ans].second){
						ans=arr[i][ans].second;
						save.push(ans+1);
					}
					fout<<i+1<<" ";
					while(!save.empty()){
						fout<<save.top()<<" ";
						save.pop();
					}
				}
			}
		}
	}
	return 0;

}
