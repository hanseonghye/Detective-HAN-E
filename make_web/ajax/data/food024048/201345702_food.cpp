#include <bits/stdc++.h>
using namespace std;


struct Edge{
    int here, there;
    Edge(int a, int b) : here(a), there(b){}
};

int TOTAL, V,E, src, dest, dpsNum = 1;
vector< vector<int> > ind;
vector<Edge> st;
vector<int> dps, ret, low, parent;
vector<bool> cut;

void changeRet(vector<int> change_ret){
    ret.clear();
    for(auto it : change_ret)
        ret.emplace_back(it);
}

void insertRet(vector<bool> check){
    vector<int> temp_ret;
    for(int i = 1; i <= V ; ++i)
        if(check[i])    temp_ret.emplace_back(i);
    if(temp_ret.size() > ret.size())
        changeRet(temp_ret);
    
    else if(temp_ret.size() == ret.size()){
        auto temp_it = temp_ret.begin();
        auto ret_it = ret.begin();
        for(;ret_it < ret.end() && *temp_it <= *ret_it ; ++ret_it, ++temp_it){
            if(*temp_it < *ret_it){
                changeRet(temp_ret);
                break;
            }
        }
    }
}

void cutVer(int here){
    dps[here] = low[here] = dpsNum++;
    int child = 0;
    for(auto there : ind[here]){
        if(dps[there] == -1){
            child++;
            parent[there] = here;
            st.emplace_back(here, there);
            cutVer(there);
            low[here] = min(low[there], low[here]);
            if((dps[here] == 1 && child > 1) ||
                (dps[here] > 1 && low[there] >= dps[here]) ){
                vector<bool> check(V+1,0);
                while(st.back().here != here || st.back().there != there){
                    check[st.back().here] = check[st.back().there] = 1;
                    st.pop_back();
                }
                check[st.back().here] = check[st.back().there] = 1;
                st.pop_back();
                insertRet(check);
            }
        }
        else if(there != parent[here] && dps[there] < low[here]){
            low[here] = min(low[here], dps[there]);
            st.emplace_back(here,there);
        }       
    }
}

int main(){
    fstream inp("food.inp", ios::in), outp("food.out", ios::out);
    inp >> TOTAL;
    V = TOTAL;

    ind = vector< vector<int> >(V+1);
    dps = vector<int>(V+1, -1);
    low = vector<int>(V+1, -1);
    parent = vector<int>(V+1, -1);
    cut  = vector<bool>(V+1, 0);

    while(TOTAL--){
        inp >> src;
        while(inp >> dest && dest){
            ind[src].emplace_back(dest);
            ind[dest].emplace_back(src);
        }
    }
    
    while(E--){
        scanf("%d %d", &src, &dest);
        
    }
    for(int i = 1 ; i <= V ; ++i){
        if(dps[i] == -1)
            cutVer(i);
        vector<bool> check(V+1,0);
        while(st.size() > 0){
            check[st.back().here] = check[st.back().there] = 1;
            st.pop_back();
        }
        insertRet(check);
    }
    for(auto it : ret)
        outp << it << " ";

   
    return 0;
}
