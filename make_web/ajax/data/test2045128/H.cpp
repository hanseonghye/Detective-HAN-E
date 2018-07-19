#include <iostream>
#include <list>
#include <fstream>

using namespace std;

ifstream fin("eleccar.inp");
ofstream fout("eleccar.out");

struct Node_ij{
    int wei;
    list <int> path;
};

void ShortestPath(Node_ij** S, int num);
void Print_result(Node_ij** S, int num);


int main(){
    int Node_Num;
    fin >> Node_Num;

    Node_ij** Node_Table = new Node_ij*[Node_Num];
    for(int i=0;i<Node_Num;i++){
        Node_Table[i] = new Node_ij[Node_Num];
    }


    for(int i=0;i<Node_Num;i++){
        for(int j=0;j<Node_Num;j++){
            fin >> Node_Table[i][j].wei;
            if(Node_Table[i][j].wei!=99999){
                Node_Table[i][j].path.push_back(i);
                Node_Table[i][j].path.push_back(j);
            }
        }
    }

    ShortestPath(Node_Table,Node_Num);

    Print_result(Node_Table,Node_Num);

    /*for(int i=0;i<Node_Num;i++){
        for(int j=0;j<Node_Num;j++){
            cout << Node_Table[i][j].wei<< " ";
        }
        cout<<endl;
    }*/









    for(int i=0;i<Node_Num;i++){
        delete[] Node_Table[i];
    }
    delete[] Node_Table;

    return 0;
}
void ShortestPath(Node_ij** S, int num){
    list <int>::iterator it;
    for(int n=0; n<num; n++){
        for(int i=0; i<num; i++){
            for(int j=0; j<num; j++){
                if(i==n) break;

                if(S[i][j].wei>(S[i][n].wei+S[n][j].wei)){
                    S[i][j].wei=(S[i][n].wei+S[n][j].wei);
                    S[i][j].path.clear();
                    for(it = S[i][n].path.begin();
                        it != S[i][n].path.end(); it++){
                            S[i][j].path.push_back(*it);
                    }
                    for(it = ++S[n][j].path.begin();
                        it != S[n][j].path.end(); it++){
                            S[i][j].path.push_back(*it);
                    }
                }
            }
        }
    }
}

void Print_result(Node_ij** S, int num){
    list <int>::iterator it;
    int diameter=0;
    int x,y;
    for(int i=0; i<num; i++){
        if(S[i][i].wei!=0){
            fout << "nega-cycle"<<endl;
            return;
        }
    }
    for(int i=0; i<num-1; i++){
        for(int j=i+1; j<num; j++){
            if(S[i][j].wei>diameter){
                x=i;
                y=j;
                diameter=S[i][j].wei;
            }
        }
    }
    fout << diameter << endl;
    if(diameter!=99999){
        for(it = S[x][y].path.begin();
            it != S[x][y].path.end(); it++){
                fout << *it+1 << " ";
        }
        fout <<  endl;
    }
}
