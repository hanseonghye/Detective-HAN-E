#include<iostream>
#include<fstream>
#include<vector>
#include<set>
#include<map>
using namespace std;

map<int, set<int>> components;
set<int>::iterator siter;
int N;
int input_buffer, source_vertex;
int answer_component, max_component_size;

pair<int, int> devideDFS(int vnum, vector<int>* templist, int* search_orders, vector<int> &path, int &order, set<int> *low_orders) {
	int low_order = order;
	int origin_order = order;
	int ret_key = order;
	for (int i = 0; i < templist[vnum].size(); i++) {
		if (search_orders[templist[vnum][i]] == 0) {
			order++;
			search_orders[templist[vnum][i]] = order;
			path.push_back(templist[vnum][i]);
			pair<int, int> child;
			child = devideDFS(templist[vnum][i], templist, search_orders, path, order, low_orders);
			path.pop_back();
			int child_return = child.first;
			int child_key = child.second;
			components[child_key].insert(vnum);
			if (child_return < origin_order) {
				if (low_order > child_return) {
					set<int>::iterator siter;
					for (siter = components[ret_key].begin(); siter != components[ret_key].end(); ++siter) {
						components[child_key].insert((*siter));
					}
					ret_key = child_key;
					low_order = child_return;
				}
				else {
					set<int>::iterator siter;
					for (siter = components[child_key].begin(); siter != components[child_key].end(); ++siter) {
						components[ret_key].insert((*siter));
					}
				}
			}
			else {}
		}
		else if (path.size() >= 2 && templist[vnum][i] != path[path.size() - 2]) {
			low_order = low_order <= search_orders[templist[vnum][i]] ? low_order : search_orders[templist[vnum][i]];
		}
	}
	low_orders[vnum].insert(low_order);
	components[origin_order].insert(vnum);
	pair<int, int> ret_pair(low_order, ret_key);
	return ret_pair;
}

void connection_check(int number, vector<int>* templist) {
	int *search_oreders = new int[number];
	set<int>* low_orders = new set<int>[number];
	map<int, set<int>>::iterator iter;
	vector<int> path;
	int order = 0;
	for (int i = 0; i < number; i++) {
		search_oreders[i] = 0;
	}
	for (int i = 0; i < number; i++) {
		if (search_oreders[i] == 0) {
			path.push_back(i);
			order++;
			search_oreders[i] = order;
			devideDFS(i, templist, search_oreders, path, order, low_orders);
		}
	}
	for (iter = components.begin(); iter != components.end(); ++iter) {
		if ((*iter).second.size() > max_component_size) {
			answer_component = (*iter).first;
			max_component_size = (*iter).second.size();
		}
		else if ((*iter).second.size() == max_component_size) {
			if (components[answer_component] > (*iter).second) {
				answer_component = (*iter).first;
				max_component_size = (*iter).second.size();
			}
		}
	}
}

int main()
{
	ifstream fin("food.inp");
	vector<int>* adjacent_list;
	fin >> N;
	adjacent_list = new vector<int>[N];
	int count = N;
	while (count--) {
		fin >> input_buffer;
		source_vertex = input_buffer - 1;
		fin >> input_buffer;
		while (input_buffer != 0) {
			adjacent_list[source_vertex].push_back(input_buffer - 1);
			fin >> input_buffer;
		}
	}
	connection_check(N, adjacent_list);
	fin.close();

	ofstream fout("food.out");
	for (siter = components[answer_component].begin(); siter != components[answer_component].end(); ++siter) {
		fout << (*siter) + 1 << " ";
	}
	fout.close();

	return 0;
}