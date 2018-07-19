#include <bits/stdc++.h>
using namespace std;

int V; 
struct Edge{
  int there;
  int cost;
  Edge(int there, int cost){
    this->there = there;
    this->cost = cost;
  }
  Edge(){}
};

const int INF = 1 << 29;
vector<Edge> graph[51];
int main(){
  freopen("eleccar.inp", "r" ,  stdin);
  freopen("eleccar.out", "w" ,  stdout);
  scanf("%d", &V);
  //cin >> V;


  for(int here=1; here<=V; here++){
    for(int there=1; there<=V; there++){
      int cost;
      scanf("%d", &cost);
      //cin >> cost;
      if(cost != 99999){
        graph[here].push_back( Edge(there, cost) );
      }
    }
  } 

  vector<int> dist(V+1, INF);
  dist[1] = 0;

  // iterator
  bool minusCycle = false;
  int path[51];
  for(int __=1; __<=V; __++){
    for(int here=1; here<=V; here++){
      for(auto hereToThere : graph[here]){
        if( dist[hereToThere.there] > dist[here] + hereToThere.cost){
          dist[hereToThere.there] = dist[here] + hereToThere.cost;
          path[hereToThere.there] = here;

          if(__ == V){
            minusCycle = true; 
          }
        } 
      }
    }
  }



  if(minusCycle){
    printf("nega-cycle\n");
  }
  else{
    int dist[51][51];
    int path[51][51];
    fill_n(*dist, 51*51, 99999); 
    fill_n(*path, 51*51, -1); 

    for(int i=1; i<=V; i++){
      for(auto j : graph[i]){
        dist[i][j.there] = j.cost; 
        path[i][j.there] = i;
      }
    }


    for(int i=1; i<=V; i++){
      for(int j=1; j<=V; j++){
        for(int k=1; k<=V; k++){
          if(dist[j][k] > dist[j][i] + dist[i][k]){
            dist[j][k] = dist[j][i] + dist[i][k];
            // j, k 의 직전 경로는 i, k 
            path[j][k] = path[i][k];
          }
        }
      } 
    }

    int maxDist = -INF;
    int maxI, maxJ;
    for(int i=1; i<=V-1; i++){
      for(int j=i+1; j<=V; j++){
        if(maxDist < dist[i][j]){
          maxDist = dist[i][j];
          maxI = i;
          maxJ = j; 
        } 
      }
    }
    
    int prev = maxJ; 
    printf("%d\n", maxDist);
    if(maxDist != 99999){
      vector<int> tracePath;
      while(prev != maxI){
        prev = path[maxI][prev];
        tracePath.push_back(prev); 
      }
      while(tracePath.empty() == false){
        printf("%d ", tracePath.back());
        tracePath.pop_back();
      }
      printf("%d ", maxJ);
    }
  }
  return 0;
}
