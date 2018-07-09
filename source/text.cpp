#include <iostream>
#include <string>
#include <cstring>
#include <vector>
#include <map>
using namespace std;

int main(int argc, char* argv[])
{
    string str_a="#Y#TYPE#TYPE#printf#scanf#12#printf#12#Y#IF#5#N#RET#N#ELSE#5#N#RET#N#ELSE#RET#RE1#9#N#8#RE1#9#N#Z#RET#N#Z";
    str_a="#0"+str_a; 

    int len_a=str_a.length();
    char str_A[len_a+1];
    vector<string> s_a;
    int count_a=0;

    strcpy(str_A,str_a.c_str());

    map<string,int> lcs_map;

    char* temp_str=strtok(str_A,"#");
    while(temp_str!=NULL){
	if(lcs_map.count(temp_str)==0){ lcs_map[temp_str]=1; }
	else { lcs_map[temp_str]=lcs_map[temp_str]+1; }

	s_a.push_back(temp_str);
	++count_a;
	temp_str=strtok(NULL,"#");
    }

	    int p=3, n=5;
	for(map<string, int>::iterator i=lcs_map.begin(); i!=lcs_map.end(); i++){
		(i->second)=32/(((i->second)*n)+p)+1;
		cout<<i->first<<" "<<i->second<<"\n";
	}



    return 0;
}

