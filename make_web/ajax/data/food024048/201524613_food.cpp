#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <stack>
#include <algorithm>

using namespace std;

struct Vertex {
	int id;		// actual ID of the vertex
	int dfn;	// the visit number by DFS
	int low;	// the number of an accessible vertex with the lowest dfs numer
	vector<int> con;	// list of connected vertices
	size_t i;			// pointer to the next connected vertex

	void init(int _id, vector<int> _con) {
		id = _id;
		con = _con;
		i = 0;
	}

	int getNextVertex() {
		if (i < con.size())
			return con[i++];
		else
			return -1;
	}
};

size_t n;				// number of vertices
int num;				// the visit nubmer by DFS
Vertex* vertices;		// array of vertices
bool* list;				// list of traversed nodes
vector<int>* maxcomp;	// the largest biconnected component
stack<int>* comp;		// for tracing through components

void compare(int id) {
	vector<int> temp;
	while (comp->top() != vertices[id].id) {
		temp.push_back(comp->top());
		comp->pop();
	}
	temp.push_back(vertices[id].id);

	// delete duplicates
	sort(temp.begin(), temp.end());
	temp.erase(unique(temp.begin(), temp.end()), temp.end());

	if (temp.size() > maxcomp->size()) {
		*maxcomp = temp;
	}
	else if (temp.size() == maxcomp->size()) {
		if(temp < *maxcomp)
			*maxcomp = temp;
	}
}

void buildBranch(int parent, int id) {
	comp->push(vertices[id].id);
	list[id] = true;
	// set dfn and low numbers
	vertices[id].dfn = vertices[id].low = num++;

	int c;
	while ((c = vertices[id].getNextVertex()) != -1) {
		if (!list[c]) { // child
			comp->push(vertices[id].id);
			buildBranch(id, c);
			if (vertices[id].dfn <= vertices[c].low) { // articulation point
				compare(id);
				comp->pop();
			}
			else if (vertices[id].low > vertices[c].low) {
				vertices[id].low = vertices[c].low;
			}
		}
		else if (c != parent) {	// if backtrack
			vertices[id].low = vertices[id].low < vertices[c].dfn ?
				vertices[id].low : vertices[c].dfn;
		}
	}
}

void buildTree() {	// build a tree using DFS
	maxcomp = new vector<int>;
	comp = new stack<int>;

	num = 0;		// the visit nubmer by DFS
	list = new bool[n] { false };
	list[0] = true;
	// set dfn and low numbers
	vertices[0].dfn = vertices[0].low = num++;

	// build the first branch
	comp->push(vertices[0].id);
	int child = vertices[0].getNextVertex();
	buildBranch(0, child);
	compare(0);

	// build other branches
	while ((child = vertices[0].getNextVertex()) != -1)
		if (!list[child]) {
			buildBranch(0, child);
			compare(0);
		}

	delete[] list;
	delete comp;
}

int main() {
	ifstream inp("food.inp", ios_base::in);
	ofstream out("food.out", ios_base::out);

	if (inp.is_open()) {
		inp >> n;
		vertices = new Vertex[n];

		for (size_t i = 0; i < n; i++) {
			int id, v;
			vector<int> list;	// list of connected vertices

			inp >> id;
			inp >> v;
			while (v != 0) {
				list.push_back(--v);
				inp >> v;
			}

			vertices[id - 1].init(id, list);
		}

		inp.close();
		// build DFS tree and find the biggest bidirectional component
		buildTree();

		if (out.is_open()) {
			for (vector<int>::const_iterator i = maxcomp->begin(); i != maxcomp->end() - 1; ++i)
				out << *i << " ";
			out << maxcomp->at(maxcomp->size() - 1);
			out.close();
		}

		delete[] vertices;
		delete maxcomp;
	}
	return 0;
}
