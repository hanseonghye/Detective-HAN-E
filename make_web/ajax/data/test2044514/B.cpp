#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#define INF 99999
#define max(a,b) (a>b?a:b)
using namespace std;

int n;
vector<vector<pair<int, int> > > inputMap;
vector<int> finalPath;
void inputData(ifstream &inStream){
    int p, q;
    inStream >> n;
    inputMap.resize(n+1);
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            inStream >> p;
            if(p == INF || p == 0) q = -1;
            else q = i;
            inputMap[i].push_back(make_pair(p,q));
        }
    }
}
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

    inputData(inStream);
    floyd();
    flag = checkNegative();
    if(flag == 0){
        int maxDistance = 0;
        for(int i = 0; i < n; i++){
            for(int j = 0; j < n; j++){
                if(i<j){
                    maxDistance = max(maxDistance, inputMap[i][j].first);
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
        int size = finalPath.size();
        for(int i = size-1; i >= 0; i--)
            outStream << finalPath.at(i) << " ";

    }else if(flag == 1){
        outStream << "nega-cycle";
    }else if(flag == 2){
        outStream << INF;
    }
    return 0;
}
