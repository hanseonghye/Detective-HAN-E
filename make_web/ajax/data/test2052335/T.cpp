#include <iostream>
#include <cmath>
#include <cstring>
#include <fstream>
#include <climits>
using namespace std;

#define EDGE_MAX 99999

int num;

int map[50][50];
int cache[50][50];

int route[50][50];

int find_min(int src){

    bool updated;
    cache[src][src] = 0;
      for(int iter = 0; iter < num; ++iter){
        updated=false;

        for(int here=0; here < num ; ++here){
            for(int i=0; i < num ; ++i){
                int there = i;
                int cost = map[here][there];

                if (cost == EDGE_MAX) continue;

                if(cache[src][there] > cache[src][here]+cost){
                    cache[src][there] = cache[src][here]+cost;
                    updated=true;
                    route[src][there] = here;
                }
            }
        }

        if(!updated) break;
    }

    if (updated) return 0;
    return 1;
}



int find_route(ofstream& fout, int src, int dest){

    if (src == dest){

        return 1;
    }

    find_route(fout, src, route[src][dest]);
    fout << route[src][dest] + 1 << " ";

}


int main()
{

	ifstream(fin);
	fin.open("eleccar.inp");
    ofstream(fout);
    fout.open("eleccar.out");
    fin >> num;

    for (int i = 0 ; i < num ; i++){
        for (int j = 0 ; j < num ; j++){
            fin >> map[i][j];
            cache[i][j] = INT_MAX - EDGE_MAX - 1;

        }
    }


    for (int i = 0 ; i < num ; i ++){
        if (find_min(i) == 0 ){
            fout << "nega-cycle" << endl;
            return 0;
        }

    }


    int src, dest;
    int max_value = INT_MIN;
    for (int i = 0 ; i < num-1 ; i++){
        for (int j = i+1 ; j < num ; j++){
            if (max_value < cache[i][j]){
                max_value = cache[i][j];
                src = i;
                dest = j;
            }
         //   cout << route[i][j] << " ";


        }

    //    cout << endl;

    }
    if (max_value == INT_MAX - EDGE_MAX - 1){
        fout << "99999" << endl;
        return 0;
    }

    fout << max_value << endl;
    find_route(fout, src, dest);
    fout << dest+1 << endl;


    fin.close();
    fout.close();
    return 0;


}
