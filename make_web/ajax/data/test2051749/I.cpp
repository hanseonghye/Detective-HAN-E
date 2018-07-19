#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
using namespace std;

string toString(int val){
	ostringstream oss;
	oss << val;
	return oss.str();
}

void floyd(int **rst, string **route, int n){
	int i, j, k;
	for (i = 0; i<n; i++){
		for (j = 0; j<n; j++){
			for (k = 0; k<n; k++){
				if (rst[j][k]>rst[j][i] + rst[i][k]){
					rst[j][k] = rst[j][i] + rst[i][k];
					route[j][k] = route[j][i] + toString(i + 1) +" "+ route[i][k];
				}
			}
		}
	}
}


int main()
{
	int N, i, j, max_value, i_value, j_value, flag = 0,len;
	ifstream ifp("eleccar.inp");
	ofstream ofp("eleccar.out");
	ifp >> N;
	string **route;
	int **rst;
	rst = new int*[N];
	route = new string*[N];
	for (i = 0; i<N; i++){
		rst[i] = new int[N];
		route[i] = new string[N];
	}

	for (i = 0; i<N; i++){
		for (j = 0; j<N; j++){
			ifp >> rst[i][j];
			if (rst[i][j] == 99999) rst[i][j]=rst[i][j] * 100;
		}
	}


	floyd(rst, route, N);


	/*
	for (i = 0; i<N; i++){
		for (j = 0; j<N; j++){
			cout << route[i][j] << " ";
		}
		cout << endl;
	}
	*/

	max_value = rst[0][0];
	i_value = 1;
	j_value = 1;
	for (i = 0; i<N; i++){
		for (j = i; j<N; j++){
			if (max_value < rst[i][j]){
				max_value = rst[i][j];
				i_value = i + 1;
				j_value = j + 1;
			}
		}
	}
	for (i = 0; i<N; i++){
		if (rst[i][i]<0){
			flag = 1;
		}
	}
	if (flag == 0){
		if (max_value == 9999900){
			ofp << "99999" << endl;
		}
		else{
			ofp << max_value << endl;
			//len = route[i_value - 1][j_value - 1].size();
			ofp << i_value<<" " ;
			ofp << route[i_value - 1][j_value - 1] ;
			//for (i = 0; i < len; i++){
			//	ofp << route[i_value - 1][j_value - 1].at(i) << " ";
			//}
			ofp << j_value << endl;
		}
	}
	else{
		ofp << "nega-cycle";
	}
	ifp.close();
	ofp.close();
	return 0;
}
