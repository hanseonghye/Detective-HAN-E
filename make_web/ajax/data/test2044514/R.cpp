#include <iostream>
#include <stack>
#include <fstream>
using namespace std;


int main(){


	ifstream fin;
	fin.open("eleccar.inp");
	ofstream fout;
	fout.open("eleccar.out");

	int not_connect = 99999;
	int node_size;
	fin >> node_size;

	int **arr = new int*[node_size];  //노드 배열 초기화
	int **via = new int*[node_size];  //노드 경로 초기화
	for (int i = 0; i < node_size; i++){
		arr[i] = new int[node_size]();
		via[i] = new int[node_size]();
	}


	for (int i = 0; i < node_size; i++){  //노드 배열의 입력
		for (int j = 0; j < node_size; j++){
			int temp;
			fin >> temp;
			arr[i][j] = temp;
		}
	}

	for (int i = 0; i < node_size; i++){
		for (int j = 0; j < node_size; j++){
			if (arr[i][j] != 99999 && arr[i][j] != 0){
				via[i][j] = i;
			}
			else{
				via[i][j] = -1;
			}
		}
	}

	int temp = 0;
	int temp_i, temp_j;

	for (int k = 0; k < node_size; k++){
		for (int i = 0; i < node_size; i++){
			for (int j = 0; j < node_size; j++){
				if (i == j&&arr[j][i] + arr[j][k] + arr[k][i] < 0){//값이 negative cycle 일때
					fout << "nega-cycle" << endl;
					return 0;
				}
				if (i == j &&arr[j][i] + arr[j][k] + arr[k][i] == 0){
					continue;
				}
				if (arr[j][i] > arr[j][k] + arr[k][i]){
					arr[j][i] = arr[j][k] + arr[k][i];
					via[j][i] = via[k][i];

				}
				if (i < j&&i != j && k == node_size - 1 && temp < arr[i][j]){
					temp = arr[i][j];
					temp_i = i;
					temp_j = j;
				}
			}
		}
	}



	if (temp != 99999){
		stack<int> roadmap;
		roadmap.push(temp_j + 1);
		int k = temp_j;

		while (temp_i != via[temp_i][k]){
			k = via[temp_i][k];
			roadmap.push(k + 1);
		}
		fout << arr[temp_i][temp_j] << endl;

		int size = roadmap.size();
		fout << temp_i + 1 << " ";
		for (int i = 0; i < size; i++){
			fout << roadmap.top() << " ";
			roadmap.pop();
		}
		fout << endl;

	}
	else if (temp == 99999){
		fout << arr[temp_i][temp_j] << endl;
	}

	return 0;
}