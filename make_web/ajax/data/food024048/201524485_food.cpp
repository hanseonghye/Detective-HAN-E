#include <iostream>
#include <vector>
#include <algorithm>
#include <fstream>
#include <cstring>

using namespace std;

int num;
vector<int> all_vertex[51];
vector<int> tmp, result;
int node, connect;
int n_size;
bool isVisit[51], isCut[51];
bool cutReady = false;

void readFile(){
	ifstream input("food.inp");
	input >> num;
	
    for(int i = 0; i < num; i++){
        input >> node;
        while(input >> connect){
            if(!connect){
            	break;
			}
            all_vertex[node].push_back(connect);
        }
    }
    input.close();
}

void DFS(int x){
    isVisit[x] = true;
    tmp.push_back(x);
    
    if(isCut[x] && cutReady){
    	return;
	}
	
    for(int i = 0; i < all_vertex[x].size(); i++){
    	if(!isVisit[all_vertex[x][i]]){
		  DFS(all_vertex[x][i]);	
		}	
	} 
}

void findLong(){
	for(int i = 1; i <= num; i++){
        DFS(i);
        n_size = tmp.size() - 1;
        tmp.clear();
		memset(isVisit, false, sizeof(isVisit));
		
        isVisit[i] = true;
        DFS(all_vertex[i][0]);
        if(tmp.size() != n_size){
        	isCut[i] = true;	
		} 
        tmp.clear();
		memset(isVisit, false, sizeof(isVisit));
    }
    
    cutReady = true;
    for(int i = 1; i <= num; i++){
        if(isCut[i]){
        	continue;
		}
		
        DFS(i);
        sort(tmp.begin(), tmp.end());
        if(tmp.size() > result.size() || (tmp.size() == result.size() && result > tmp)){
        	result = tmp;	
		} 
        tmp.clear();
		memset(isVisit, false, sizeof(isVisit));
    }
}

void writeFile(){
	ofstream output("food.out");
	
    for(int i = 0; i < result.size(); i++){
    	output << result[i] << " ";
	} 
	for(int i = 0; i < result.size(); i++){
    	cout << result[i] << " ";
	} 
    output.close();
}

int main()
{
    readFile();
    findLong();
    writeFile();

    return 0;
}

