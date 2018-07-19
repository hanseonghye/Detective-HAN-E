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

// 한 vertex와 연결되어 있는 edge
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

// 한 vertex
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

	// debug 용
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

	// 첫 vertex label 리턴
	int firstVertexLabel();
	bool isEmpty();

	// debug 용
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

	// 입력 받아오기 시작
	ifs.open(if_name);
	if (!ifs.is_open()) {
		cout << if_name << " 파일이 안 열렸어요" << endl;
		return 0;
	}
	int inValue;
	int inLabel;
	bool inNewLine = true;

	ifs >> num_vertex;

	// vertex 만들기
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
	// 입력 받아오기 끝

	//graph.printGraph();

	if (graph.isEmpty()) {
		cout << "그래프에 아무것도 없어요" << endl;
		return 0;
	}

	// cut vertex (articulation point) 구하기

	vector<int> cutVertices;

	// DFSnum[i] 는 (i + 1) vertex 의 DFS number
	int *DFSnum = new int[num_vertex];
	// lownum[i] 는 (i + 1) vertex 의 low number
	int *lownum = new int[num_vertex];
	// DFS 방문한 vertex 인지 boolean
	bool *visited = new bool[num_vertex];
	for (int i = 0; i < num_vertex; ++i) {
		visited[i] = false;
	}

	int newDFSnum = 1;

	// 컴포넌트를 저장하기 위해
	// 검사한 Edge 저장하는 stack
	stack<EdgeNode*> visitedEdgeStack;
	
	// biconnected component들 저장하는 곳
	vector<int> *biconnectedComponents = new vector<int>[num_vertex];
	int indexComponent = 0;
	
	// 처음부터 아예 연결이 안 된 컴포넌트도 고려
	// DFS 시작점은 1 vertex
	for (int v = 1; v <= num_vertex; ++v) {
		if (visited[v - 1] == false) {
	
			
			stack<int> DFSstack;
			DFSstack.push(v);
			int firstVertex = v;
			DFSnum[firstVertex - 1] = newDFSnum++;
			visited[firstVertex - 1] = true;
			lownum[firstVertex - 1] = firstVertex;


			// 시작점의 child 개수, 2개 이상이면 시작점은 cut vertex
			int childOfStart = 0;

			while (!DFSstack.empty()) {
				// DFS stack의 top에 있는 vertex와 연결되어 있는 adj vertex 중 방문 안 한 vertex 찾기
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

				// 아직 방문 안 한 vertex 찾은 경우
				if (findNoVisited) {

					// 시작점 인 경우
					if (DFSstack.top() == v) {
						++childOfStart;

						// 시작점의 DFS 트리 자식이 두 개 이상이면 시작점도 cut vertex
						if (childOfStart >= 2) {
							cutVertices.push_back(v);

							// biconnected 하나 찾아서 만들기
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
				// 주위에 방문 안 한 vertex가 없는 경우
				else {

					// low num 정해주기
					int curVertex = DFSstack.top();
					DFSstack.pop();

					// 현재 vertex가 DFS search 시작점이 아닐 때
					if (!DFSstack.empty()) {
						int parentVertex = DFSstack.top();

						for (int i = 0; i < graph.vertex(curVertex)->getNumEdges(); ++i) {
							int adjVertex = graph.vertex(curVertex)->getEdge(i)->getDest()->getLabel();
							// DFS tree에서의 부모 vertex 제외
							if (adjVertex != parentVertex) {
								// low number보다 주위에 갈 수 있는 vertex 들의 DFS num가 더 낮을 때 바꾸기
								if (lownum[curVertex - 1] > DFSnum[adjVertex - 1]) {
									lownum[curVertex - 1] = DFSnum[adjVertex - 1];

									// backedge
									//visitedEdgeStack.push(graph.vertex(curVertex)->getEdge(i));

									//cout << "push " << graph.vertex(curVertex)->getEdge(i)->getSource()->getLabel() << " " << graph.vertex(curVertex)->getEdge(i)->getDest()->getLabel() << endl;
								}
							}
						}

						// 부모 vertex 의 low number가 자식 vertex 의 low number 보다 큰 경우
						if (lownum[parentVertex - 1] > lownum[curVertex - 1]) {
							lownum[parentVertex - 1] = lownum[curVertex - 1];
						}

						// 부모 DFS num이 자식 low number 보다 작거나 같을 때 부모 vertex는 cut vertex
						if (DFSnum[parentVertex - 1] <= lownum[curVertex - 1]) {
							// 부모 vertex 시작점일 때 제외
							if (parentVertex != v) {
								cutVertices.push_back(parentVertex);
								
								// biconnected 하나 찾아서 만들기
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
						
						// 시작점의 DFS 트리 자식이 두 개 이상이면 시작점도 cut vertex
						/*if (childOfStart >= 2) {
							cutVertices.push_back(v);
						}*/
					}
				}
			}
			
			// stack에 남은거도 componenet 만들어주기
			while (!visitedEdgeStack.empty()) {
				biconnectedComponents[indexComponent].push_back(visitedEdgeStack.top()->getDest()->getLabel());
				biconnectedComponents[indexComponent].push_back(visitedEdgeStack.top()->getSource()->getLabel());

				visitedEdgeStack.pop();
			}
			++indexComponent;

		}
	}

	// cut vertex 중복 제거
	sort(cutVertices.begin(), cutVertices.end());
	cutVertices.erase(unique(cutVertices.begin(), cutVertices.end()), cutVertices.end());
	
	// cut vertex 출력
	cout << "cut vertex " << endl;
	for (vector<int>::iterator it = cutVertices.begin(); it != cutVertices.end(); ++it) {
		cout << *it << " ";
	}
	cout << endl;

	int maxSizeComponent = 0;
	int maxSizeIndex = -1;

	cout << "biconnected componenet 수 : " << indexComponent << endl;
	for (int i = 0; i < num_vertex; ++i) {
		if (!biconnectedComponents[i].empty()) {
			// 중복 제거
			sort(biconnectedComponents[i].begin(), biconnectedComponents[i].end());
			biconnectedComponents[i].erase(unique(biconnectedComponents[i].begin(), biconnectedComponents[i].end()), biconnectedComponents[i].end());

			// 더 큰 컴포넌트
			if (biconnectedComponents[i].size() > maxSizeComponent) {
				maxSizeComponent = biconnectedComponents[i].size();
				maxSizeIndex = i;
			}
			// 제일 큰 컴포넌트와 크기가 같을 경우 오름차순으로 빠른
			else if (!biconnectedComponents[i].empty() &&
				biconnectedComponents[i].size() == maxSizeComponent &&
				biconnectedComponents[i] < biconnectedComponents[maxSizeIndex]) {
				maxSizeComponent = biconnectedComponents[i].size();
				maxSizeIndex = i;
			}

			cout << i << "번 째 ";
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
		cout << "output file이 안 열렸어요" << endl;
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
