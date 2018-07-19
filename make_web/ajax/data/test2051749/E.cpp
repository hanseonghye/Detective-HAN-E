#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;
template<class T>
string to_string(T t){

    ostringstream ss;
    ss<< t;
    return ss.str();

}

int main()
{
    ifstream fin("eleccar.inp");
    ofstream fout("eleccar.out");

    int num;
    fin >> num;
    int large = 0;
    int **arr = new int* [num];
    int **dist = new int* [num];
    string **path = new string* [num];

    for(int i=0; i<num; i++) {
        arr[i] = new int[num];
        dist[i] = new int[num];
        path[i] = new string[num];
    }

    for(int i=0; i<num; i++) {
        for(int j=0; j<num; j++) {
            fin >> arr[i][j];
            dist[i][j] = arr[i][j];
            path[i][j]= to_string(i+1);
        }
    }

    //floyd
    for(int k=0; k<num; k++) {
        for(int i=0; i<num; i++) {
            for(int j=0; j<num; j++) {
                if(dist[i][j] > dist[i][k] + dist[k][j]) {
                    dist[i][j] = dist[i][k] + dist[k][j];
                    path[i][j] = path[i][k] +" " + path[k][j];
                }
            }
        }
    }

    string answer;
    int chk = 1;
    for(int i=0; i<num; i++) {
        for(int j=0; j<num; j++) {
            if(dist[i][i]<0) {
                chk = 0;
                break;
            }
            if(dist[i][j] == 99999) {
                chk = 2;
                break;
            }
            if(dist[i][j]>large && (j>i)) {
                large = dist[i][j];
                answer = path[i][j] + " " + to_string(j+1);
            }
        }
        if(chk == 0)
            break;
    }

    if(chk==0) {
        fout << "nega-cycle" << endl;
    }
    else if(chk==2) {
        fout << "99999" << endl;
    }
    else {
        fout << large << endl;
        fout << answer << endl;
    }

    return 0;
}

