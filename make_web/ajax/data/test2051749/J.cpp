#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>
#include <algorithm>
#define MAX 55
#define INPUT "eleccar.inp"
#define OUTPUT "eleccar.out"

using namespace std;

int cost[MAX][MAX];
int via[MAX][MAX];

int main() {

    ifstream inpStream(INPUT) ;
	ofstream outStream(OUTPUT) ;

	int N = 0;

	inpStream >> N;

	for(int i = 0 ; i < N ; ++i) {
        for(int j = 0 ; j < N ; ++j) {
            inpStream >> cost[i][j];
            if(i == j) { cost[i][j] = 0; }
            if(cost[i][j] < 20000) { via[i][j] = i; }
            else { cost[i][j] = MAX * 99999; }
        }
	}

	for(int k = 0 ; k < N ; ++k) {
        for(int i = 0 ; i < N ; ++i) {
            if(cost[i][k] == MAX * 99999) { continue; }
            for(int j = 0 ; j < N ; ++j) {
                if(cost[k][j] == MAX * 99999) { continue; }
                if(cost[i][j] > cost[i][k] + cost[k][j]) {
                    cost[i][j] = cost[i][k] + cost[k][j];
                    via[i][j] = k;
                }
                if(cost[i][j] + cost[j][i] < 0) {
                    //outStream << i+1 << ' ' << j+1 << '\n';
                    outStream << "nega-cycle\n";
                    return 0;
                }
            }
        }
	}

	int diameter = MAX * -99999;
    int start, finish;

    for(int i = 0 ; i < N ; ++i) {
        for(int j = i+1 ; j < N ; ++j) {
            if(cost[i][j] >= MAX * 99999) {
                //outStream << i+1 << ' ' << j+1 << '\n';
                outStream << "99999\n";
                return 0;
            }
            if(cost[i][j] > diameter) {
                diameter = cost[i][j];
                start = i;
                finish = j;
            }
        }
    }

    int path[MAX];
    int pathSize = 1;
    path[0] = finish;
    int passed[MAX] = {};
    while(start != finish) {
        int viaStart = via[start][finish];
        while((viaStart != via[viaStart][finish]) && (passed[via[viaStart][finish]] == 0)) {
            viaStart = via[viaStart][finish];
        }
        path[pathSize] = viaStart;
        ++pathSize;
        finish = viaStart;
        passed[viaStart] = 1;
    }
    outStream << diameter << '\n';
    for(int i = pathSize-1 ; i >= 0 ; --i) {
        outStream << path[i]+1 << ' ';
    }
    outStream << '\n';

	return 0;
}
