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
    int score=0;
    int mmax=0;

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
        (m_iter->second)=len3/(((m_iter->second)*n)+p);
    }
/*
    int spe=7;
    if(lcs_map.count("IF")!=0) lcs_map["IF"]=lcs_map["IF"]+spe-2;
    if(lcs_map.count("FOR")!=0) lcs_map["FOR"]=lcs_map["FOR"]+spe;
    if(lcs_map.count("WHILE")!=0) lcs_map["WHILE"]=lcs_map["WHILE"]+spe;
    if(lcs_map.count("RE1")!=0) lcs_map["RE1"]=lcs_map["RE1"]+spe;
    if(lcs_map.count("RE2")!=0) lcs_map["RE2"]=lcs_map["RE2"]+spe;

    if(lcs_map.count("ID")!=0) lcs_map["ID"]=lcs_map["ID"]/3;
  */ 
    int **lcs=new int*[count_a];
    int **table=new int*[count_a];
    int **re=new int*[count_a];

    for(int i=0;i<count_a;++i){
        lcs[i]=new int[count_b];
        table[i]=new int[count_b];
        re[i]=new int[count_b];
    }
    int m;

    for(int i=0;i<count_a;++i){
        for(int j=0; j<count_b;++j){
            if(i==0||j==0){
                lcs[i][j]=0;
                table[i][j]=0;
                continue;
            }
            if(s_a[i]==s_b[j]){
                table[i][j]=table[i-1][j-1]+5;
		if(table[i][j]>30) { lcs[i][j]=lcs[i-1][j-1]+lcs_map[s_a[i]];}
		else lcs[i][j]=0;

            }
            else{
                table[i][j]=table[i-1][j-1]-3;
                lcs[i][j]=0;

                if(table[i][j]<0)   table[i][j]=0;
            }

            if(m<lcs[i][j]) m=lcs[i][j];


        }
    }

    if(str_a.compare(str_b)==0) {cout<<m;  return 0;}

    for(int i=0;i<count_a;++i){
        for(int j=0;j<count_b;++j){
                if(i==0||j==0) {re[i][j]=0; continue; }
            	if(lcs[i][j]==0){
                int pplus=0;
                for(int k=0;k<j;++k){ if(lcs[i-1][k]>pplus) pplus=lcs[i-1][k]; }
                for(int k=0;k<i;++k){ if(lcs[k][j-1]>pplus) pplus=lcs[k][j-1]; }
                re[i][j]=pplus;
            }
            else{
                int k=1;
                while(1){
                    if(lcs[i-k][j-k]==0) break;
                    ++k;
                }
                re[i][j]=lcs[i][j]+re[i-k][j-k];
                if(mmax<re[i][j])   mmax=re[i][j];
            }

        }
    }

    for(int i=0;i<count_a;++i){
        delete [] lcs[i];
        delete [] table[i];
        delete [] re[i];
    }

    delete [] lcs;
    delete [] table;
    delete [] re;

    s_a.clear(); s_b.clear();

  
    cout<<mmax;


    return 0;
}

