#include <stdio.h>
#include <fstream>
#include <sstream>
#include <string>
#include <cstring>
using namespace std;

string intToString(int a){
    stringstream s;
    s << a;
    return s.str();
}

int main(){
    int N, dist[50][50];
    string path[50][50],temp;

    FILE * finp = fopen("eleccar.inp","r");
    //ofstream fout("eleccar.out");
    FILE * fout = fopen("eleccar.out","w");

	fscanf(finp,"%d", &N);

    for(int i=0; i<N; i++){
        temp=to_string(i+1);
        for(int j=0; j<N; j++){
            fscanf(finp,"%d",&dist[i][j]);
            path[i][j] = temp;
        }
    }

    for(int k=0; k<N; k++){ // 플로이드 워셜 알고리즘
        for(int i=0; i<N; i++){
            for(int j=0; j<N; j++){
                if(dist[i][k] == 99999) break;
                if(dist[i][j] > dist[i][k]+dist[k][j]){
                    dist[i][j] = dist[i][k]+dist[k][j];
                    path[i][j] = path[i][k] + " " + path[k][j];
                }
            }
        }
    }

    int stCity=0,enCity=1, flag=0;
    for(int i=0; i<N; i++){
        if(dist[i][i] < 0) {
            flag=1;
            break;
        }
    }
    if( flag==0){
        for(int i=0; i<N; i++){
            for(int j=i+1; j<N; j++){
                if(dist[stCity][enCity] < dist[i][j] ) { // 최대 찾기
                    stCity=i;
                    enCity=j;
                }
            }
        }
    }


    char *tempC = new char[path[stCity][enCity].length()];
    strcpy(tempC, path[stCity][enCity].c_str());

    if(flag==1) fprintf(fout,"nega-cycle");//fout << "nega-cycle"  ;
    else{
        fprintf(fout,"%d\n", dist[stCity][enCity]); //fout << dist[stCity][enCity] << endl;
        if(dist[stCity][enCity] != 99999) fprintf(fout,"%s %d", tempC ,enCity+1);//fout << path[stCity][enCity] + " " +to_string(enCity+1) ;

    }
}
