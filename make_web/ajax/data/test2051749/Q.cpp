#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;

ifstream infile("eleccar.inp");
ofstream outfile("eleccar.out");

class eleccar{
private:
    int total;
    int **arr;
    int **before;
    int num;
    int sign;
    vector <int> path;
public:
    void get_info();
    void search_loot();
};
void eleccar::get_info(){
    infile >> total;

    arr = new int*[total];
    for(int i = 0; i < total; ++i) {
        arr[i] = new int[total];
    }
    for(int i=0; i < total; i++){
        for(int j=0; j < total; j++){
            infile >> num;
            arr[i][j] = num;
        }
    }
     before = new int*[total];
    for(int i = 0; i < total; ++i) {
        before[i] = new int[total];
    }
    for(int i=0; i < total; i++){
        for(int j=0; j < total; j++){
                if(arr[i][j]!=99999)
                    before[i][j] = i;
                else
                    before[i][j] = 99999;
        }
    }
}
void eleccar::search_loot(){
    sign =0; // sign 0 work , sign -1 nega ,sign 1 99999
     // Do Floyd-Warshall Algorithm
    for (int k = 0; k < total; k++){

        if(sign == -1 ){
            break;
        }

        for (int i = 0; i < total; i++){
            if(arr[i][i] < 0){
                    sign = -1;
                }
            for (int j = 0; j < total; j++){

                if (arr[i][j] > arr[i][k] + arr[k][j]){
                    arr[i][j] = arr[i][k] + arr[k][j];
                    before[i][j] = before[k][j];
                }
            }
        }
    }
    if(sign!=-1){
        for (int i = 0; i < total; i++){
            for (int j = 0; j < total; j++){
                if(arr[i][j]==99999)
                        sign = 1;
            }
        }
    }
    int max_dia= -999999;
    int max_i;
    int max_j;

    if(sign == 0){
         for (int i = 0; i < total; i++){
            for (int j = 0; j < total; j++){
                if (arr[i][j] > max_dia && i < j){
                    max_dia = arr[i][j];
                    max_i = i;
                    max_j = j;
                }
            }
        }
        path.push_back(max_j);
        while(max_i != max_j ){
            max_j = before[max_i][max_j] ;
            path.push_back(max_j);

        }

        outfile << max_dia << endl;
        for(vector<int>::iterator it = path.end()-1 ; it != path.begin();it--){
            outfile << (*it)+1 << " " ;
            path.pop_back();
        }
        outfile << (path.back())+1 ;
    }

    else if( sign == -1 ){
        outfile << "nega-cycle" << endl;
    }
    else if(sign == 1){
        outfile << "99999" << endl;
    }

}


int main()
{
    eleccar play;
    play.get_info();
    play.search_loot();
    return 0;
}
