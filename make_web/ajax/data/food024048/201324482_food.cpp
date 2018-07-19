#include<iostream>
#include<fstream>
#include<vector>
#include<set>
#include<map>
using namespace std;
void DFSdriver(int vertex, int &commonent_number, vector<int>* adjacent_list, int* search_oreders) {
	for (int i = 0; i < adjacent_list[vertex].size(); i++) {
		if (search_oreders[adjacent_list[vertex][i]] == 0) {
			search_oreders[adjacent_list[vertex][i]] = commonent_number;
			DFSdriver(adjacent_list[vertex][i], commonent_number, adjacent_list, search_oreders);
		}
	}
}
map<int, set<int>> connected_components;
pair<int,int> DFSdriver2(int vertex, vector<int>* adjacent_list, int* search_orders, int* cut_vertex, vector<int> &path,int &order, set<int> *low_orders) {
	set<int>* new_connected_component;
	int low_order = order;
	int origin_order = order;
	int ret_key = order;
	for (int i = 0; i < adjacent_list[vertex].size(); i++) {
		if (search_orders[adjacent_list[vertex][i]] == 0) {
			order++;
			search_orders[adjacent_list[vertex][i]] = order;
			path.push_back(adjacent_list[vertex][i]);
			cout << "PATH:";
			for (int j = 0; j < path.size(); j++) {
				cout << path[j] << " ";
			}cout << endl;
			pair<int, int> child;
			child = DFSdriver2(adjacent_list[vertex][i], adjacent_list, search_orders, cut_vertex, path, order, low_orders);
			path.pop_back();
			int child_return = child.first;
			int child_key = child.second;
			connected_components[child_key].insert(vertex);
			//zz
			//low_orders[vertex].insert(child_return);
			//connected_components[child_return].insert(vertex);
			if (child_return < origin_order) {
				//단절점이 아니야, 한 뭉탱이
				if (low_order > child_return) {
					set<int>::iterator siter;
					for (siter = connected_components[ret_key].begin(); siter != connected_components[ret_key].end(); ++siter) {
						connected_components[child_key].insert( (*siter));
					}
					ret_key = child_key;
					low_order = child_return;
				}
				else {
					set<int>::iterator siter;
					for (siter = connected_components[child_key].begin(); siter != connected_components[child_key].end(); ++siter) {
						connected_components[ret_key].insert((*siter));
					}
				}
			}
			else if(child_return >= origin_order){
				//단절점
				cout << "단절점: " << vertex<<" ("<< origin_order<<", "<< child_return << ")"<< endl;
				cut_vertex[vertex] ++;
			}
		}
		else if(path.size()>=2&&adjacent_list[vertex][i] != path[path.size()-2]){
			low_order = low_order <= search_orders[adjacent_list[vertex][i]] ? low_order : search_orders[adjacent_list[vertex][i]];
		}
	}
	cout <<vertex<<" : "<< origin_order << " " << low_order << endl;
	low_orders[vertex].insert(low_order);
	//zz
	//connected_components[low_order].insert(vertex);
	connected_components[origin_order].insert(vertex);
	pair<int, int> ret_pair(low_order, ret_key);
	return ret_pair;
}
void connection_check(int N, vector<int>* adjacent_list) {
	ofstream fout("food.out");
	int connection_number = 0;
	int *search_oreders = new int[N];
	
	int *cut_vertex = new int[N];
	set<int>* low_orders = new set<int>[N];
	int order = 0;
	
	for (int i = 0; i < N; i++) {
		search_oreders[i] = 0;
		cut_vertex[i] = 0;
	}
	
	for (int i = 0; i < N; i++) {
		if (search_oreders[i] == 0) {
			vector<int> path;
			path.push_back(i);
			order++;
			search_oreders[i] = order;
			DFSdriver2(i, adjacent_list, search_oreders, cut_vertex, path, order, low_orders);
		}
	}
	if (cut_vertex[0] <= 1)cut_vertex[0] = 0;
	for (int i = 0; i < N; i++) {
		cout << cut_vertex[i];
	}
	cout << endl;
	for (int j = 0; j < N; j++) {
		cout << search_oreders[j] << "_";
	}cout << endl;

	int answer_component = 0;
	int max_component_size = 0;
	map<int, set<int>>::iterator iter;
	set<int>::iterator siter;
	for (iter = connected_components.begin(); iter != connected_components.end(); ++iter) {
		cout << (*iter).first << " (" << (*iter).second.size() << ") :";
		for (siter = (*iter).second.begin(); siter != (*iter).second.end(); ++siter) {
			cout << (*siter) << " ";
		}cout << endl;
		if ((*iter).second.size() > max_component_size) {
			answer_component = (*iter).first;
			max_component_size = (*iter).second.size();
		}
		else if ((*iter).second.size() == max_component_size) {
			if (connected_components[answer_component] > (*iter).second) {
				answer_component = (*iter).first;
				max_component_size = (*iter).second.size();
			}
			/*set<int>::iterator siter2 = (*iter).second.begin();
			for (siter = connected_components[answer_component].begin(); siter != connected_components[answer_component].end(); ++siter) {
				if ((*siter) > (*siter2)) {
					answer_component = (*iter).first;
					max_component_size = (*iter).second.size();
					break;
				}
				++siter2;
			}*/
		}
	}
	cout << answer_component<<","<< max_component_size<<endl;
	for (siter = connected_components[answer_component].begin(); siter != connected_components[answer_component].end(); ++siter) {
		fout << (*siter)+1 << " ";
	}
	fout.close();
}

void TEST_list(int N, vector<int>* adjacent_list) {
	for (int i = 0; i < N; i++) {
		cout.width(2);
		cout << i<< ":";
		for (int j = 0; j< adjacent_list[i].size(); j++) {
			cout << " " << adjacent_list[i][j];
		}
		cout << endl;
	}

}

int main()
{
	ifstream fin("food.inp");
	//ofstream fout("food.out");
	vector<int>* adjacent_list;
	int num_of_vertex;
	fin >> num_of_vertex;
	adjacent_list = new vector<int>[num_of_vertex];
	
	/*for (int i = 0; i < num_of_vertex; i++) {
		int input_buffer;
		fin >> input_buffer;
		input_buffer;
		while(input_buffer != 0) {
			adjacent_list[i].push_back(input_buffer);
			fin >> input_buffer;
		}
	}*/
	//====================================================================
	//	최적화된 인풋 알고리즘
	//	vector<int> array의 인덱스가 source vertex이다. 
	//--------------------------------------------------------------------
	//	이 알고리즘을 쓸 경우, vertex number가 1부터 num_of_vertex까지여야 함.
	//	이번 과제에선 위의 가정을 보장할 수 있으니 이 알고리즘을 쓴다.
	//====================================================================
	int input_cnt = num_of_vertex;
	while (input_cnt--) {
		int input_buffer;
		fin >> input_buffer;
		int source_vertex = input_buffer - 1;
		fin >> input_buffer;
		while (input_buffer != 0) {
			adjacent_list[source_vertex].push_back(input_buffer-1);
			fin >> input_buffer;
		}
	}
	//======================================================================
	//	connection_check test case
	//======================================================================
	/*vector<int> a,b,c;
	vector<int> *adjacent_list2;
	int num_of_vertex2 = 3;
	adjacent_list2 = new vector<int>[num_of_vertex2];
	a = { 2};
	b = {2 };
	c = { 0,1 };

	adjacent_list2[0] = a;
	adjacent_list2[1] = b;
	adjacent_list2[2] = c;

	TEST_list(num_of_vertex2,adjacent_list2);
	connection_check(num_of_vertex2, adjacent_list2);
	*/
	//=======================================================================
	TEST_list(num_of_vertex, adjacent_list);
	connection_check(num_of_vertex, adjacent_list);
	fin.close();
	//fout.close();
	return 0;
}