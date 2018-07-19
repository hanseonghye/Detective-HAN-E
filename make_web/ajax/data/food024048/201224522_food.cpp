#include <iostream>
#include <string>
#include <fstream>
#include <stack>
#include <vector>
#include <algorithm>

using namespace std;

class EdgeNode;
class VertexNode;
class Graph;

// �� vertex�� ����Ǿ� �ִ� edge
class EdgeNode {
	friend class VertexNode;
private:
	VertexNode *from;
	VertexNode *to;

public:
	EdgeNode(VertexNode* source, VertexNode* dest) : from(source), to(dest) {}

	VertexNode* getSource();
	VertexNode* getDest();
};

// �� vertex
class VertexNode {
	friend class Graph;
private:
	// adjacent Edge list
	vector<EdgeNode*> adjEdge;
	int label;

public:
	VertexNode(int label) : label(label) {}
	~VertexNode();

	bool add_edge(VertexNode* dest);

	int getLabel();
	int getNumEdges();
	EdgeNode* getEdge(int index);

	// debug ��
	void printEdges();
};

class Graph {
private:
	// vertex list
	vector<VertexNode*> vertices;

public:
	~Graph();

	VertexNode* vertex(int label);

	bool add_vertex(int label);

	// ù vertex label ����
	int firstVertexLabel();
	bool isEmpty();

	// debug ��
	void printGraph();
};

VertexNode::~VertexNode()
{
	while (!adjEdge.empty()) {
		EdgeNode* tempEdge = adjEdge.back();
		adjEdge.pop_back();
		delete tempEdge;
	}
}

bool VertexNode::add_edge(VertexNode * dest)
{
	EdgeNode *edge = new EdgeNode(this, dest);
	adjEdge.push_back(edge);

	return true;
}

int VertexNode::getLabel()
{
	return label;
}

int VertexNode::getNumEdges()
{
	return adjEdge.size();
}

EdgeNode * VertexNode::getEdge(int index)
{
	if (index < 0 && index > getNumEdges() - 1)
		return NULL;
	return adjEdge.at(index);
}

void VertexNode::printEdges()
{
	vector<EdgeNode*>::iterator it;
	for (it = adjEdge.begin(); it != adjEdge.end(); ++it) {
		cout << (*it)->to->label << " ";
	}
	cout << endl;
}

Graph::~Graph()
{
	while (!vertices.empty()) {
		VertexNode* tempVertex = vertices.back();
		vertices.pop_back();
		delete tempVertex;
	}
}

VertexNode * Graph::vertex(int label)
{
	vector<VertexNode*>::iterator it;
	for (it = vertices.begin(); it != vertices.end(); ++it) {
		if ((*it)->label == label) {
			return *it;
		}
	}
	return NULL;
}

bool Graph::add_vertex(int label)
{
	VertexNode *node = new VertexNode(label);
	vertices.push_back(node);

	return true;;
}

int Graph::firstVertexLabel()
{
	if (isEmpty()) return -1;
	return vertices.at(0)->label;
}

bool Graph::isEmpty()
{
	if (vertices.empty()) {
		return true;
	}
	return false;
}

void Graph::printGraph() {
	vector<VertexNode*>::iterator it_vertices;
	for (it_vertices = vertices.begin(); it_vertices != vertices.end(); ++it_vertices) {
		cout << (*it_vertices)->label << " - ";
		(*it_vertices)->printEdges();
	}
}


VertexNode * EdgeNode::getSource()
{
	return from;
}

VertexNode * EdgeNode::getDest()
{
	return to;
}


int main() {
	const int maxNumVertex = 50;
	const string if_name = "food.inp";
	const string of_name = "food.out";
	

	ifstream ifs;
	ofstream ofs;
	
	Graph graph;
	int num_vertex = 0;

	// �Է� �޾ƿ��� ����
	ifs.open(if_name);
	if (!ifs.is_open()) {
		cout << if_name << " ������ �� ���Ⱦ��" << endl;
		return 0;
	}
	int inValue;
	int inLabel;
	bool inNewLine = true;

	ifs >> num_vertex;

	// vertex �����
	for (int i = 0; i < num_vertex; ++i) {
		graph.add_vertex(i + 1);
	}

	while (ifs >> inValue) {
		if (inValue == 0) {
			inNewLine = true;
		}
		else if (inNewLine) {
			inNewLine = false;
			inLabel = inValue;
			
		}
		else {
			graph.vertex(inLabel)->add_edge(graph.vertex(inValue));
		}
	}

	ifs.close();
	// �Է� �޾ƿ��� ��

	//graph.printGraph();

	if (graph.isEmpty()) {
		cout << "�׷����� �ƹ��͵� �����" << endl;
		return 0;
	}

	// cut vertex (articulation point) ���ϱ�

	vector<int> cutVertices;

	// DFSnum[i] �� (i + 1) vertex �� DFS number
	int *DFSnum = new int[num_vertex];
	// lownum[i] �� (i + 1) vertex �� low number
	int *lownum = new int[num_vertex];
	// DFS �湮�� vertex ���� boolean
	bool *visited = new bool[num_vertex];
	for (int i = 0; i < num_vertex; ++i) {
		visited[i] = false;
	}

	int newDFSnum = 1;

	// ������Ʈ�� �����ϱ� ����
	// �˻��� Edge �����ϴ� stack
	stack<EdgeNode*> visitedEdgeStack;
	
	// biconnected component�� �����ϴ� ��
	vector<int> *biconnectedComponents = new vector<int>[num_vertex];
	int indexComponent = 0;
	
	// ó������ �ƿ� ������ �� �� ������Ʈ�� ���
	// DFS �������� 1 vertex
	for (int v = 1; v <= num_vertex; ++v) {
		if (visited[v - 1] == false) {
	
			
			stack<int> DFSstack;
			DFSstack.push(v);
			int firstVertex = v;
			DFSnum[firstVertex - 1] = newDFSnum++;
			visited[firstVertex - 1] = true;
			lownum[firstVertex - 1] = firstVertex;


			// �������� child ����, 2�� �̻��̸� �������� cut vertex
			int childOfStart = 0;

			while (!DFSstack.empty()) {
				// DFS stack�� top�� �ִ� vertex�� ����Ǿ� �ִ� adj vertex �� �湮 �� �� vertex ã��
				bool findNoVisited = false;
				int nextVertex;
				EdgeNode* nextEdge;
				for (int i = 0; i < graph.vertex(DFSstack.top())->getNumEdges(); ++i) {
					// adj vertex
					nextVertex = graph.vertex(DFSstack.top())->getEdge(i)->getDest()->getLabel();
					if (!visited[nextVertex - 1]) {
						findNoVisited = true;
						nextEdge = graph.vertex(DFSstack.top())->getEdge(i);
						break;
					}
				}

				// ���� �湮 �� �� vertex ã�� ���
				if (findNoVisited) {

					// ������ �� ���
					if (DFSstack.top() == v) {
						++childOfStart;

						// �������� DFS Ʈ�� �ڽ��� �� �� �̻��̸� �������� cut vertex
						if (childOfStart >= 2) {
							cutVertices.push_back(v);

							// biconnected �ϳ� ã�Ƽ� �����
							while (!visitedEdgeStack.empty()) {
								biconnectedComponents[indexComponent].push_back(visitedEdgeStack.top()->getDest()->getLabel());
								biconnectedComponents[indexComponent].push_back(visitedEdgeStack.top()->getSource()->getLabel());

								//cout << visitedEdgeStack.top()->getDest()->getLabel() << " " << visitedEdgeStack.top()->getSource()->getLabel() << " ";

								if (visitedEdgeStack.top()->getSource()->getLabel() == v) {
									visitedEdgeStack.pop();
									break;
								}
								visitedEdgeStack.pop();
							}

							//cout << endl;

							++indexComponent;
						}
					}

					visitedEdgeStack.push(nextEdge);

					//cout << "push " << nextEdge->getSource()->getLabel() << " " << nextEdge->getDest()->getLabel() << endl;

					DFSnum[nextVertex - 1] = newDFSnum++;
					visited[nextVertex - 1] = true;
					DFSstack.push(nextVertex);
					lownum[nextVertex - 1] = DFSnum[nextVertex - 1];

				}
				// ������ �湮 �� �� vertex�� ���� ���
				else {

					// low num �����ֱ�
					int curVertex = DFSstack.top();
					DFSstack.pop();

					// ���� vertex�� DFS search �������� �ƴ� ��
					if (!DFSstack.empty()) {
						int parentVertex = DFSstack.top();

						for (int i = 0; i < graph.vertex(curVertex)->getNumEdges(); ++i) {
							int adjVertex = graph.vertex(curVertex)->getEdge(i)->getDest()->getLabel();
							// DFS tree������ �θ� vertex ����
							if (adjVertex != parentVertex) {
								// low number���� ������ �� �� �ִ� vertex ���� DFS num�� �� ���� �� �ٲٱ�
								if (lownum[curVertex - 1] > DFSnum[adjVertex - 1]) {
									lownum[curVertex - 1] = DFSnum[adjVertex - 1];

									// backedge
									//visitedEdgeStack.push(graph.vertex(curVertex)->getEdge(i));

									//cout << "push " << graph.vertex(curVertex)->getEdge(i)->getSource()->getLabel() << " " << graph.vertex(curVertex)->getEdge(i)->getDest()->getLabel() << endl;
								}
							}
						}

						// �θ� vertex �� low number�� �ڽ� vertex �� low number ���� ū ���
						if (lownum[parentVertex - 1] > lownum[curVertex - 1]) {
							lownum[parentVertex - 1] = lownum[curVertex - 1];
						}

						// �θ� DFS num�� �ڽ� low number ���� �۰ų� ���� �� �θ� vertex�� cut vertex
						if (DFSnum[parentVertex - 1] <= lownum[curVertex - 1]) {
							// �θ� vertex �������� �� ����
							if (parentVertex != v) {
								cutVertices.push_back(parentVertex);
								
								// biconnected �ϳ� ã�Ƽ� �����
								while (!visitedEdgeStack.empty()) {
									biconnectedComponents[indexComponent].push_back(visitedEdgeStack.top()->getDest()->getLabel());
									biconnectedComponents[indexComponent].push_back(visitedEdgeStack.top()->getSource()->getLabel());
									//cout << visitedEdgeStack.top()->getDest()->getLabel() << " " << visitedEdgeStack.top()->getSource()->getLabel() << " ";
									
									if (visitedEdgeStack.top()->getSource()->getLabel() == parentVertex ||
										visitedEdgeStack.top()->getDest()->getLabel() == curVertex) {
										visitedEdgeStack.pop();
										break;
									}
									visitedEdgeStack.pop();
								}

								//cout << endl;

								++indexComponent;
							}
						}
					}
					else {
						
						// �������� DFS Ʈ�� �ڽ��� �� �� �̻��̸� �������� cut vertex
						/*if (childOfStart >= 2) {
							cutVertices.push_back(v);
						}*/
					}
				}
			}
			
			// stack�� �����ŵ� componenet ������ֱ�
			while (!visitedEdgeStack.empty()) {
				biconnectedComponents[indexComponent].push_back(visitedEdgeStack.top()->getDest()->getLabel());
				biconnectedComponents[indexComponent].push_back(visitedEdgeStack.top()->getSource()->getLabel());

				visitedEdgeStack.pop();
			}
			++indexComponent;

		}
	}

	// cut vertex �ߺ� ����
	sort(cutVertices.begin(), cutVertices.end());
	cutVertices.erase(unique(cutVertices.begin(), cutVertices.end()), cutVertices.end());
	
	// cut vertex ���
	cout << "cut vertex " << endl;
	for (vector<int>::iterator it = cutVertices.begin(); it != cutVertices.end(); ++it) {
		cout << *it << " ";
	}
	cout << endl;

	int maxSizeComponent = 0;
	int maxSizeIndex = -1;

	cout << "biconnected componenet �� : " << indexComponent << endl;
	for (int i = 0; i < num_vertex; ++i) {
		if (!biconnectedComponents[i].empty()) {
			// �ߺ� ����
			sort(biconnectedComponents[i].begin(), biconnectedComponents[i].end());
			biconnectedComponents[i].erase(unique(biconnectedComponents[i].begin(), biconnectedComponents[i].end()), biconnectedComponents[i].end());

			// �� ū ������Ʈ
			if (biconnectedComponents[i].size() > maxSizeComponent) {
				maxSizeComponent = biconnectedComponents[i].size();
				maxSizeIndex = i;
			}
			// ���� ū ������Ʈ�� ũ�Ⱑ ���� ��� ������������ ����
			else if (!biconnectedComponents[i].empty() &&
				biconnectedComponents[i].size() == maxSizeComponent &&
				biconnectedComponents[i] < biconnectedComponents[maxSizeIndex]) {
				maxSizeComponent = biconnectedComponents[i].size();
				maxSizeIndex = i;
			}

			cout << i << "�� ° ";
			for (vector<int>::iterator it = biconnectedComponents[i].begin(); it != biconnectedComponents[i].end(); ++it) {
				cout << *it << " ";
			}
			cout << endl;
		}
	}
/*
	cout << maxSizeIndex << endl;*/
	for (vector<int>::iterator it = biconnectedComponents[maxSizeIndex].begin();
		it != biconnectedComponents[maxSizeIndex].end(); ++it) {
		cout << *it << " ";
	}
	cout << endl;

	ofs.open(of_name);
	if (!ofs.is_open()) {
		cout << "output file�� �� ���Ⱦ��" << endl;
	}
	else {
		for (vector<int>::iterator it = biconnectedComponents[maxSizeIndex].begin();
			it != biconnectedComponents[maxSizeIndex].end(); ++it) {
			ofs << *it << " ";
		}
	}

	delete[] biconnectedComponents;
	delete[] DFSnum;
	delete[] lownum;
	delete[] visited;
	return 0;
}
