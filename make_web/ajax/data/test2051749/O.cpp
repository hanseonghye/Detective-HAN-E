#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cstring>
using namespace std;

#define INF 99999

void print(int s, int t);

typedef struct max{
	int i;
	int j;
	int value;
} Max;

int path[51][51];
FILE *in, *out;

int main(){
	in = fopen("eleccar.inp", "r");
	out = fopen("eleccar.out", "w");

	int N;
	int city[51][51];

	fscanf(in, "%d", &N);

	for(int i = 1; i <= N; i++){
		for(int j = 1; j <= N; j++){
			fscanf(in, "%d", &city[i][j]);
		}
	}

	for(int k = 1; k <= N; k++){
		for(int i = 1; i <= N; i++){
			for(int j = 1; j <= N; j++){
				if(city[i][j] > city[i][k] + city[k][j]){
					city[i][j] = city[i][k] + city[k][j];
					path[i][j] = k;
				}
			}
		}
	}

	int s, t, max = -99999;
	for(int i = 1; i <= N; i++){
		if(city[i][i] < 0){
			fprintf(out, "%s", "nega-cycle");
			return 0;
		}
		for(int j = i; j <= N; j++){
			if(city[i][j] == INF){
				fprintf(out, "%d\n", INF);
				return 0;
			}
			if(max < city[i][j]){
				max = city[i][j];
				s = i;
				t = j;
			}
		}
	}

	fprintf(out, "%d\n", max);
	fprintf(out, "%d ", s);
	print(s, t);
	fprintf(out, "%d\n", t);

	return 0;
}
void print(int s, int t){
	if(path[s][t] != 0){
		print(s, path[s][t]);
		fprintf(out, "%d ", path[s][t]);
		print(path[s][t], t);
	}
}