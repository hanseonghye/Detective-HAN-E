#include <fstream>
#include <string>

using namespace std;

#define VERTEX_MAX 51

int routeGraph[26][26] ;
int friends[3] ;
int visit[3][26] ;
int dist[3][26] ;
int vertexOfDegree[26] ;
int maxDist[26] ;
int numOfNode ;


void Floyd_Warshall(int NodeNumber, int(*Distance)[VERTEX_MAX], string(*NodeTable_String)[VERTEX_MAX]);
void dijkstra(int startNode, int friendsNum);

int main()
{

	const char *in = "eleccar.inp";
	const char *out = "eleccar.out";

	int iCount = 0;
	int Max_Length = -1;
	int Max_StartNode = 1;
	int Max_EndNode = 1;
	int Number_Node = 0;

	string NodeTable_String[VERTEX_MAX][VERTEX_MAX];
	int Length[VERTEX_MAX][VERTEX_MAX];
	ifstream in_file(in);
	ofstream out_file(out);



	while (!in_file.eof())  // 파일의 끝이 아니라면
	{
		// 처음파일 읽을때
		
		in_file >> Number_Node;

		for (int StartNode = 1; StartNode <= Number_Node; StartNode++)
		{
			for (int y = 1; y <= Number_Node; y++)
			{
				in_file >> Length[StartNode][y];
				NodeTable_String[StartNode][y] = to_string(StartNode);
			}
		}

		Floyd_Warshall(Number_Node, Length, NodeTable_String);

		for (int StartNode = 1; StartNode <= Number_Node; StartNode++)
		{
			for (int EndNode = 1; EndNode <= Number_Node; EndNode++)
			{
				if (StartNode == EndNode )
				{
					if( Length[StartNode][EndNode] < 0){
					out_file << "nega-cycle";
					return 0;
					}
				}
				if (Max_Length < Length[StartNode][EndNode]) 
				{
					if(StartNode < EndNode){
						Max_Length = Length[StartNode][EndNode];
						Max_StartNode = StartNode;
						Max_EndNode = EndNode;
					}
				}
				if (Length[StartNode][EndNode] == 99999)
				{
					out_file << "99999";
					return 0;
				}
			}
		}

		out_file << Max_Length << endl;
		out_file << NodeTable_String[Max_StartNode][Max_EndNode] + " " + to_string(Max_EndNode);

		in_file.close();
		out_file.close();
	}
	return 0;
}

void Floyd_Warshall(int NodeNumber, int(*Distance)[VERTEX_MAX], string(*NodeTable_String)[VERTEX_MAX])
{
	for (int ViaNode = 1; ViaNode <= NodeNumber; ViaNode++)
	{
		for (int StartNode = 1; StartNode <= NodeNumber; StartNode++)
		{
			for (int EndNode = 1; EndNode <= NodeNumber; EndNode++)
			{
				if (Distance[StartNode][EndNode] > Distance[StartNode][ViaNode] + Distance[ViaNode][EndNode])
				{
					Distance[StartNode][EndNode] = Distance[StartNode][ViaNode] + Distance[ViaNode][EndNode];
					NodeTable_String[StartNode][EndNode] = NodeTable_String[StartNode][ViaNode] + " " + NodeTable_String[ViaNode][EndNode];
				}
			}
		}
	}
}



void dijkstra(int startNode, int friendsNum) {
    int temp = vertexOfDegree[startNode] ;
    vertexOfDegree[startNode] = 0 ;
    dist[friendsNum][startNode] = 0 ;
    int minDist ;
    int vertex ;

    for ( int i = 0 ; i < numOfNode ; i ++) {
        minDist = 99999 ;
        for (int j = 0 ; j < numOfNode ; j ++) {
            if ( visit[friendsNum][j] == 0 && minDist > dist[friendsNum][j]) {
                minDist = dist[friendsNum][j] ;
                vertex = j ;
            }
        }
        visit[friendsNum][vertex] = 1 ;
        for (int k = 0 ; k < numOfNode ; k ++ ) {
            if ( i == 0 && dist[friendsNum][k] > dist[friendsNum][vertex] + routeGraph[vertex][k] ) {
                dist[friendsNum][k] = dist[friendsNum][vertex] + routeGraph[vertex][k] + vertexOfDegree[vertex] ;
            }
            else if (i != 0 && dist[friendsNum][k] > dist[friendsNum][vertex] + routeGraph[vertex][k] + vertexOfDegree[vertex] ) {
                dist[friendsNum][k] = dist[friendsNum][vertex] + routeGraph[vertex][k] + vertexOfDegree[vertex] ;
            }
        }
    }
    vertexOfDegree[startNode] = temp ;
}

