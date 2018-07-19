#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<algorithm>

using namespace std;


int main(){
	ifstream inFile("eleccar.inp");
	ofstream outFile("eleccar.out");
	int count, change;
	int map[50][50], map2[50][50];
	int i, j, k, p, tmp, tmp2, max; //calc max ( i->j , i->k->j 
	string path[50][50], maxs;
	char c[6];
	char zero='0';
	
	inFile>>count;
	for(i=0;i<count; i++){
		for(j=0;j<count;j++){
			inFile>>map[i][j];
			map2[i][j]=map[i][j];
			maxs="";
			//sprintf(c,"%d %d",i+1,j+1);
			//tmp=0;
			k=i+1;
			p=j+1;
			if(k/10>0) maxs+=zero+k/10; //path[i][j];
			maxs+=zero+k%10;
			maxs+=' ';
			if(p/10>0) maxs+=zero+p/10; //tmp+=1;
			maxs+=zero+p%10;
			//c[3+tmp]=0;
			path[i][j]+=maxs;
		}
	}
	
	//shortest long path
	for(p=0;p<count; p++){ //n try...
		change=0;
		for(i=0;i<count;i++){
			for(j=0;j<count;j++){
				tmp = map2[i][j];
				for(k=0;k<count;k++){
					tmp2 = map2[i][k]+map[k][j]; //new one + original one
					if(tmp2 + map2[j][i]<0){
						outFile<<"nega-cycle";
						return 0;
					}
					if(tmp>tmp2){
						change++;
						tmp = tmp2;
						max=j+1;
						path[i][j] = path[i][k];
						path[i][j]+=' ';
						if(max/10>0) path[i][j]+=zero+max/10;
						path[i][j] += zero+max%10; //i~k j
					}
				}
				map2[i][j]=tmp;
			}
		}
		if(change==0){
			break;
		} 
	}
	if(change!=0){
		outFile<<"nega-cycle";
		return 0;
	}
	max=-99999;
	for(i=0; i<count; i++){
		for(j=i+1;j<count;j++){
			if(max<map2[i][j]){
				max=map2[i][j];
				maxs=path[i][j];
			}
		}
	}
	j = maxs.length();
	outFile << max;
	if(max!=99999) outFile<< endl << maxs;
}

