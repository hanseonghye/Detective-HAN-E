#include <fstream>
#include <string>

using namespace std;



int Node_count = 0;
string nd_String[51][51];
int Length[51][51];

void Floyd_Warshall()
{
	for (int ViaNode = 1; ViaNode <= Node_count; ViaNode++)
	{
		for (int StartNode = 1; StartNode <= Node_count; StartNode++)
		{
			for (int EndNode = 1; EndNode <= Node_count; EndNode++)
			{
				if (Length[StartNode][EndNode] > Length[StartNode][ViaNode] + Length[ViaNode][EndNode])
				{
					Length[StartNode][EndNode] = Length[StartNode][ViaNode] + Length[ViaNode][EndNode];
					nd_String[StartNode][EndNode] = nd_String[StartNode][ViaNode] + " " + nd_String[ViaNode][EndNode];
				}
			}
		}
	}
}

int main()
{

	const char *in = "eleccar.inp";
	const char *out = "eleccar.out";

	int iCount = 0;
	int Max_Length = -1;
	int Max_StartNode = 1;
	int Max_EndNode = 1;
	ifstream in_file(in);
	ofstream out_file(out);



	while (!in_file.eof())  // 파일의 끝이 아니라면
	{
		// 처음파일 읽을때
		iCount++;
		if (iCount == 1)
		{
			in_file >> Node_count;
		}

		for (int StartNode = 1; StartNode <= Node_count; StartNode++)
		{
			for (int y = 1; y <= Node_count; y++)
			{
				in_file >> Length[StartNode][y];
				nd_String[StartNode][y] = to_string(StartNode);
			}
		}

		Floyd_Warshall();

		for (int StartNode = 1; StartNode <= Node_count; StartNode++)
		{
			for (int EndNode = 1; EndNode <= Node_count; EndNode++)
			{
				if (StartNode == EndNode && Length[StartNode][EndNode] < 0)
				{
					out_file << "nega-cycle";
					return 0;
				}
				if (Max_Length < Length[StartNode][EndNode] && (StartNode < EndNode))
				{
					Max_Length = Length[StartNode][EndNode];
					Max_StartNode = StartNode;
					Max_EndNode = EndNode;
				}
				if (Length[StartNode][EndNode] == 99999)
				{
					out_file << "99999";
					return 0;
				}
			}
		}

		out_file << Max_Length << endl;
		out_file << nd_String[Max_StartNode][Max_EndNode] + " " + to_string(Max_EndNode);

		in_file.close();
		out_file.close();
	}
	return 0;
}
