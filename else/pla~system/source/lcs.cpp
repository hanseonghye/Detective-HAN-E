#include <iostream>
#include <string>
#include <cstring>
#include <vector>
#include <map>
using namespace std;

int main(int argc, char* argv[])
{
    string str_a=argv[1];
    string str_b=argv[2];
    str_a="#0"+str_a; 
    str_b="#0"+str_b;

    int len_a=str_a.length();
    int len_b=str_b.length();

    char str_A[len_a+1], str_B[len_b+1];
    vector<string> s_a, s_b;
    int count_a=0, count_b=0;

    strcpy(str_A,str_a.c_str());
    strcpy(str_B,str_b.c_str());


    map<string,int> lcs_map;

    char* temp_str=strtok(str_A,"#");
    while(temp_str!=NULL){
	if(lcs_map.count(temp_str)==0){ lcs_map[temp_str]=1; }
	else { lcs_map[temp_str]=lcs_map[temp_str]+1; }

	s_a.push_back(temp_str);
	++count_a;
	temp_str=strtok(NULL,"#");
    }

    char* temp_str2=strtok(str_B,"#");
    while(temp_str2!=NULL){
	//if(lcs_map.count(temp_str2)==0){ lcs_map[temp_str2]=1; }
	//else { lcs_map[temp_str2]=lcs_map[temp_str2]+1; }
	s_b.push_back(temp_str2);
	++count_b;
	temp_str2=strtok(NULL,"#");
    }

    map<string, int>::iterator m_iter;
    int len3=(count_a);
    int p=3, n=5;
    for(m_iter=lcs_map.begin(); m_iter!=lcs_map.end();++m_iter){
        (m_iter->second)=len3/(((m_iter->second)*n)+p)+1;
    }

    int **lcs=new int*[count_a];
    int **table=new int*[count_a];

    for(int i=0;i<count_a;++i){
        lcs[i]=new int[count_b];
        table[i]=new int[count_b];
    }

    int score=0;
    int m=0;
    for(int i=0;i<count_a;++i){
        for(int j=0; j<count_b;++j){
	    int big1=0, big2=0;
	    score=0;

            if(i==0||j==0){
                lcs[i][j]=0;
                table[i][j]=0;
                continue;
            }
            if(s_a[i]==s_b[j]){
                table[i][j]=table[i-1][j-1]+3;
		if(table[i][j]>15) { score=lcs_map[s_a[i]];}
		else score=0;
            }
            else{
                table[i][j]=table[i-1][j-1]-2;
                if(table[i][j]<0)   table[i][j]=0;
            }

	    big1=lcs[i-1][j]>lcs[i][j-1]?lcs[i-1][j]:lcs[i][j-1];
	    big2=lcs[i-1][j-1]+score;
            lcs[i][j]=big1>big2 ? big1 : big2;
	    if(m<lcs[i][j]) m=lcs[i][j];
        }
    }


    for(int i=0;i<count_a;++i){
        delete [] lcs[i];
        delete [] table[i];
    }

    delete [] lcs;
    delete [] table;

    s_a.clear(); s_b.clear();

  
    cout<<m;


    return 0;
}

