#include <iostream>
#include <vector>

using namespace std;
int IND[105][105];
int D[105][105];
bool acop[105][105];
int N,M;
vector<pair<pair<int,int>,int> > E;
vector<int> G[105];
bool viz[105];
int dfs(int nod,int tata){
   viz[nod] = 1;
   for(auto it:G[nod]){
      if(it != tata && !viz[it]){
         dfs(it,nod);
      }
   }
}
int main() {
    cin >> N >> M;
    for(int i = 1;i <= N;i++){
       for(int j = 1;j <= N;j++){
          D[i][j] = (i == j ? 0 : 1 << 28);
       }
    }
    for(int i = 1;i <= M;i++){
       int a,b,c;
       cin >> a >> b >> c;
       if(IND[a][b] && IND[a][b] != c){
          cout << -1;
          return 0;
       }
       IND[a][b] = D[a][b] = c;
       IND[b][a] = D[b][a] = c;
    }
    for(int k = 1;k <= N;k++){
       for(int i = 1;i <= N;i++){
          if(k == i){
             continue;
          }
          for(int j = 1;j <= N;j++){
             if(k == i || k == j){
                continue;
             }
            if(D[i][j] > D[i][k] + D[k][j]){
               D[i][j] = D[i][k] + D[k][j];
               acop[i][j] = 1;
            }
          }
       }
    }
    for(int i = 1;i <= N;i++){
       for(int j = 1;j <= N;j++){
          if(IND[i][j] && D[i][j] != IND[i][j]){
             cout << -1;
             return 0;
          }
          if(j >= i && IND[i][j] && !acop[i][j]){
             E.push_back({{i,j},IND[i][j]});
             G[i].push_back(j);
             G[j].push_back(i);
             M--;
          }
       }
    }
    int leg = 1;
    for(int i = 1;i <= N;i++){
       if(!viz[i]){
          dfs(i,0);
          if(leg != i){
             E.push_back({{leg,i},1e7});
             acop[leg][i] = 1;
             acop[i][leg] = 1;
             M--;
          }
       }
    }
    int u,v;
    u = 1,v = 2;
    cout << E.size() << "\n";
    for(auto it:E){
       cout << it.first.first << " " << it.first.second << " " << it.second << "\n";
    }
    return 0;
}
