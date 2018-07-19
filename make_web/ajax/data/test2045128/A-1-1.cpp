#include <fstream>
#include <string>

using namespace std;

#define VERTEX_MAX 51
#define nine 99999




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

int cmp(string a, string b){
	string aa = a;
	string bb = b;
	int i, size;
	
	size = a.size();
	for(i=0;i<size; i++){
		if(aa[i]=='c') aa[i]='u';
		else if(aa[i]!='a'&&aa[i]!='g'&&aa[i]!='t'){
			aa[i]='z';
		}
	}
	
	size=b.size();
	for(i=0;i<size; i++){
		if(bb[i]=='c') bb[i]='u';
		else if(bb[i]!='a'&&bb[i]!='g'&&bb[i]!='t'){
			bb[i]='z';
		}
	}
	
	return aa.compare(bb);
}

int main()
{
	int Max_StartNode = 1;
	int Max_EndNode = 1;
	int Number_Node = 0;

	const char *in = "eleccar.inp";
	const char *out = "eleccar.out";

	int iCount = 0;
	int Max_Length = -1;

	ifstream in_file(in);
	ofstream out_file(out);

	string NodeTable[VERTEX_MAX][VERTEX_MAX];
	int Length[VERTEX_MAX][VERTEX_MAX];


	in_file >> Number_Node;


	for (int StartNode = 1; StartNode <= Number_Node; StartNode++)
	{
		for (int y = 1; y <= Number_Node; y++)
		{
			in_file >> Length[StartNode][y];
			NodeTable[StartNode][y] = to_string(StartNode);
		}
	}

	Floyd_Warshall(Number_Node, Length, NodeTable);

	for (int StartNode = 1; StartNode <= Number_Node; StartNode++)
	{
		for (int EndNode = 1; EndNode <= Number_Node; EndNode++)
		{
			if (StartNode == EndNode ) 
			{
				if(Length[StartNode][EndNode] < 0)
				{
					out_file << "nega-cycle";
					return 0;
				}
			}
			if (Max_Length < Length[StartNode][EndNode])
			{
				if(StartNode < EndNode)
				{
					Max_Length = Length[StartNode][EndNode];
					Max_StartNode = StartNode;
					Max_EndNode = EndNode;
				}
			}
			if (Length[StartNode][EndNode] == nine)
			{
				out_file << nine;
				return 0;
			}
		}
	}

	out_file << Max_Length << "\n";
	out_file << NodeTable[Max_StartNode][Max_EndNode] +" "+to_string(Max_EndNode);

	in_file.close();
	out_file.close();
	
	return 0;
}
