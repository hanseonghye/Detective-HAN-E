#include <iostream>
#include <fstream>
#include <deque>
#include <algorithm>

using namespace std;

int n;
deque<deque<pair<int, int> > > inputMap;
deque<int> finalPath;


void floyd(){
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            for(int k = 0; k < n; k++){
                if(inputMap[j][k].first > inputMap[j][i].first + inputMap[i][k].first){
                    inputMap[j][k].first = inputMap[j][i].first + inputMap[i][k].first;
                    inputMap[j][k].second = inputMap[i][k].second;
                }
            }
        }
    }
}


int checkNegative(){
    int flag = 0;
    for(int i = 0; i < n; i++){
        int num = 0;
        for(int j = 0; j < n; j++){
            if( i == j && inputMap[i][j].second != -1){
                flag = 1;
            }
            if(inputMap[i][j].second == -1) num++;
        }
        if(num == n){
            flag = 2;
        }
    }
    return flag;
}


int main(){
    int flag;
    ifstream inStream("eleccar.inp");
    ofstream outStream("eleccar.out");

    int p, q;
    inStream >> n;
    inputMap.resize(n+1);
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            inStream >> p;
            if(p == 99999 || p == 0) q = -1;
            else q = i;
            inputMap[i].push_back(make_pair(p,q));
        }
    }

    floyd();
    flag = checkNegative();

    if(flag == 1){ outStream << "nega-cycle"; return 0;}
    if(flag == 2){ outStream << 99999; return 0;}
    if(flag == 0){

        int maxDistance = 0;

        for(int i = 0; i < n; i++){
            for(int j = 0; j < n; j++){
                if(i<j){
                    maxDistance =maxDistance > inputMap[i][j].first? maxDistance :inputMap[i][j].first;
                }
            }
        }
   
        for(int i = 0; i < n; i++){
            for(int j = 0; j < n; j++){
                if(maxDistance == inputMap[i][j].first){
                    int pre = j;
                    finalPath.push_back(pre + 1);
                    while(i != inputMap[i][pre].second){
                        pre = inputMap[i][pre].second;
                        finalPath.push_back(pre + 1);
                    }
                    finalPath.push_back(i+1);
                }
            }
        }

        outStream << maxDistance << endl;

        long size = finalPath.size();
        for(int i = size-1; i >= 0; i--)
            outStream << finalPath.at(i) << " ";
    }
    return 0;
}
