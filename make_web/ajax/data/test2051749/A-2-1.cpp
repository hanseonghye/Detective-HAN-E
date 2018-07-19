#include <fstream>
#include <string>

using namespace std;

#define VERTEX_MAX 51
#define ROAD_LOST 99999
#define N nega-cycle


int iCount = 0;
int LengthMax = -1;
int StartNodeMax = 1;
int EndNodeMax = 1;
int NodeNumber = 0;

int main()
{
	const char *pInputFileName = "eleccar.inp";
	const char *pOutputFileName = "eleccar.out";

	string NodeTable_String[VERTEX_MAX][VERTEX_MAX];
	int Length[VERTEX_MAX][VERTEX_MAX];
	ifstream InFile(pInputFileName);
	ofstream OutFile(pOutputFileName);

	InFile >> NodeNumber;

	for (int i = 1; i <= NodeNumber; i++)
	{
		for (int y = 1; y <= NodeNumber; y++)
		{
			InFile >> Length[i][y]; 
			NodeTable_String[i][y] = to_string(i);
		}
	}
	InFile.close();

	for (int i = 1; i <= NodeNumber; i++)
	{
		for (int j = 1; j <= NodeNumber; j++)
		{
			for (int k = 1; k <= NodeNumber; k++)
			{
				if (Length[j][k] > ( Length[j][i] + Length[i][k]))
				{
					Length[j][k] = Length[j][i] + Length[i][k];
					NodeTable_String[j][k] = NodeTable_String[j][i] + " " + NodeTable_String[i][k];
				}
			}
		}
	}


	for (int i = 1; i <= NodeNumber; i++)
	{
		for (int j = 1; j <= NodeNumber; j++)
		{
			if (i == j && Length[i][j] < 0){ OutFile << N; return 0; }
			if (LengthMax < Length[i][j] && (i < j))
			{
				LengthMax = Length[i][j];
				EndNodeMax = j;
				StartNodeMax = i;
			}
			if (Length[i][j] == ROAD_LOST){	OutFile << "99999"; return 0; }
		}
	}

	OutFile << LengthMax <<"\n";
	OutFile << NodeTable_String[StartNodeMax][EndNodeMax] + " ";
	OutFile << to_string(EndNodeMax);


	OutFile.close();
	
	return 0;
}
