#include <fstream>
#include <string>

using namespace std;

#define VERTEX_MAX 51
#define ROAD_LOST 99999



//161017_Floyd_Warshall Functionized
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

int main()
{
	const char *pInputFileName = "eleccar.inp";
	const char *pOutputFileName = "eleccar.out";

	string NodeTable_String[VERTEX_MAX][VERTEX_MAX];
	int Length[VERTEX_MAX][VERTEX_MAX];
	ifstream InFile(pInputFileName);
	ofstream OutFile(pOutputFileName);

	int iCount = 0;
	int LengthMax = -1;
	int StartNodeMax = 1;
	int EndNodeMax = 1;
	int NodeNumber = 0;

	while (!InFile.eof())  // 파일의 끝이 아니라면
	{
		// 처음파일 읽을때
		iCount++;
		if (iCount == 1)
		{
			InFile >> NodeNumber;
		}

		for (int StartNode = 1; StartNode <= NodeNumber; StartNode++)
		{
			for (int y = 1; y <= NodeNumber; y++)
			{
				InFile >> Length[StartNode][y];
				NodeTable_String[StartNode][y] = to_string(StartNode);
			}
		}

		Floyd_Warshall(NodeNumber, Length, NodeTable_String);

		for (int StartNode = 1; StartNode <= NodeNumber; StartNode++)
		{
			for (int EndNode = 1; EndNode <= NodeNumber; EndNode++)
			{
				if (StartNode == EndNode && Length[StartNode][EndNode] < 0)
				{
					OutFile << "nega-cycle";
					return 0;
				}
				if (LengthMax < Length[StartNode][EndNode] && (StartNode < EndNode))
				{
					LengthMax = Length[StartNode][EndNode];
					StartNodeMax = StartNode;
					EndNodeMax = EndNode;
				}
				if (Length[StartNode][EndNode] == ROAD_LOST)
				{
					OutFile << "99999";
					return 0;
				}
			}
		}

		OutFile << LengthMax << endl;
		OutFile << NodeTable_String[StartNodeMax][EndNodeMax] + " " + to_string(EndNodeMax);

		InFile.close();
		OutFile.close();
	}
	return 0;
}