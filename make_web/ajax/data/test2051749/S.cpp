#include <iostream>
#include <stdio.h>
using namespace std;


int* arr = new int[50];
int num = 0;

void print_path(int **P, int q, int r) { // P����� �̿��ؼ� q���� r������ �̵� ��θ� ���
	if (P[q][r] != 0) {
		print_path(P, q, P[q][r]);
		//cout << P[q][r] << " ";
		arr[num++] = P[q][r];
		print_path(P, P[q][r], r);
	}
}

int main() {
	int number_of_node;
	int negative = 0;

	//FILE *input_file = fopen("C:\\Users\\Administrator\\Desktop\\sampleData4\\1.inp", "r");
	//FILE *output_file = fopen("C:\\Users\\Administrator\\Desktop\\sampleData4\\return.out", "w");

	FILE *input_file = fopen("eleccar.inp", "r");
	FILE *output_file = fopen("eleccar.out", "w");

	fscanf(input_file, "%d", &number_of_node);


	int **D = new int*[number_of_node];		//D :�������
	int **P = new int*[number_of_node];		//P : �������� ���� ���� Node�� ���� ���� ū Node
	int **min = new int*[number_of_node];	//min : �� Node������ �ּҰ�� ��
	for (int i = 0; i < number_of_node; i++)
		D[i] = new int[number_of_node];
	for (int i = 0; i < number_of_node + 1; i++)
		P[i] = new int[number_of_node + 1];
	for (int i = 0; i < number_of_node; i++)
		min[i] = new int[number_of_node];

	//D,P,min �ʱ�ȭ
	for (int i = 0; i < number_of_node; i++) {
		for (int j = 0; j < number_of_node; j++) {
			fscanf(input_file, "%d", &D[i][j]);
			min[i][j] = D[i][j];
			P[i][j] = 0;
		}
	}
	for (int i = 0; i < number_of_node + 1; i++) {
		for (int j = 0; j < number_of_node + 1; j++) {
			P[i][j] = 0;
		}
	}

	//min,P �� ���
	for (int k = 0; k < number_of_node; k++) {
		for (int i = 0; i < number_of_node; i++) {
			for (int j = 0; j < number_of_node; j++) {
				if (min[i][j] > min[i][k] + min[k][j]) {
					min[i][j] = min[i][k] + min[k][j];
					P[i + 1][j + 1] = k + 1;
				}
			}
		}
	}

	//max���� �� x,y�� return
	int max_value = min[0][0];	int max_x; int max_y;
	for (int i = 0; i < number_of_node; i++) {
		for (int j = i+1; j < number_of_node; j++) {
			if (min[i][j] > max_value) {
				max_value = min[i][j];
				max_x = i;	max_y = j;
			}
		}
	}

	for (int i = 0; i < number_of_node; i++) {
		if (min[i][i] < 0)
			negative = 1;
	}
	
	if (max_value != 99999 && (!negative)) {
		//cout << max_value << endl;
		fprintf(output_file, "%d\n", max_value);

		//cout << max_x + 1 << " ";
		fprintf(output_file, "%d ", max_x + 1);

		print_path(P, max_x + 1, max_y + 1);

		for (int i = 0; i < num; i++)
			fprintf(output_file, "%d ", arr[i]);

		//cout << max_y + 1 << endl;
		fprintf(output_file, "%d ", max_y + 1);
	}
	else if (negative) {
		//cout << "nega-cycle" << endl;
		fprintf(output_file, "nega-cycle");
	}
	else if (max_value == 99999) {
		//cout << "99999" << endl;
		fprintf(output_file, "99999\n");
	}
	else {
		//cout << "error !!" << endl;
		fprintf(output_file, "error !!\n");
	}
	
	fclose(output_file);
	fclose(input_file);
	return 0;
}
