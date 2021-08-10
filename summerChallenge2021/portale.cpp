#include <bits/stdc++.h>

using namespace std;

const int NMAX = 1e2;

int t;
int n;
int adj[NMAX + 5][NMAX + 5];
int lvl[NMAX + 5];
int weight[NMAX + 5];

pair<int,int> ask(const pair<int,int> &edge){
  pair<int,int> ans;
  cout << "? " << edge.first << " " << edge.second << endl;
  cin >> ans.first >> ans.second;
  return ans;
}

void answer(){
  cout << "!" << endl;
  for(int i = 1;i <= n;i++){
    for(int j = i + 1;j <= n;j++){
      if(adj[i][j]){
        cout << i << " " << j << endl;
      }
    }
  }
}

void predfs(int nod,int tata){
  weight[nod] = 1;
  lvl[nod] = 1 + lvl[tata];
  for(int it = 1;it <= n;it++){
    if(adj[nod][it] == 0 || it == tata){
      continue;
    }
    predfs(it,nod);
    weight[nod] += weight[it];
  }
}



int getCentroid(int nod){
  predfs(nod,0);
  int father = 0;
  int totalWeight = weight[nod];

  while(true){
    int bigChild = -1;
    
    for(int it = 1;it <= n;it++){
      if(adj[nod][it] == 0 || it == father){
        continue;
      }
      if(bigChild == -1 || weight[it] > weight[bigChild]){
        bigChild = it;
      }
    }

    if(bigChild == -1 || 2 * weight[bigChild] <= totalWeight){
      break;
    }

    father = nod;
    nod = bigChild;
  }
  
  predfs(nod,0);

  return nod;
}

void solve(int newNode,int rootUnknown){
  int centroidUnknown = getCentroid(rootUnknown);
  if(weight[centroidUnknown] == 1){
    adj[newNode][rootUnknown] = adj[rootUnknown][newNode] = 1;
    return ;
  }
  pair<int,int> edge = make_pair(newNode,centroidUnknown);
  pair<int,int> ans = ask(edge);
      
  if(ans.first == 0 && ans.second == 0){
    adj[edge.first][edge.second] = adj[edge.second][edge.first] = 1;
    return ;
  }else if(adj[ans.first][ans.second] == 0){
    adj[edge.first][edge.second] = adj[edge.second][edge.first] = 1;
    return ;
  }else{
    adj[ans.first][ans.second] = adj[ans.second][ans.first] = 0;
    adj[edge.first][edge.second] = adj[edge.second][edge.first] = 1;
    if(lvl[ans.first] > lvl[ans.second]){
      swap(ans.first,ans.second);
    }
    solve(newNode,ans.second);
  }
}

int main(){
  cin >> t;

  while(t--){
    cin >> n;

    for(int i = 2;i <= n;i++){
      pair<int,int> edge = make_pair(getCentroid(1),i);
      pair<int,int> ans = ask(edge);
      if(ans.first == 0 && ans.second == 0){
        adj[edge.first][edge.second] = adj[edge.second][edge.first] = 1;
        continue;
      }else if(adj[ans.first][ans.second] == 0){
        adj[edge.first][edge.second] = adj[edge.second][edge.first] = 1;
        continue;
      }else{
        adj[ans.first][ans.second] = adj[ans.second][ans.first] = 0;
        adj[edge.first][edge.second] = adj[edge.second][edge.first] = 1;
        if(lvl[ans.first] > lvl[ans.second]){
          swap(ans.first,ans.second);
        }
        solve(i,ans.second);
      }
    }

    answer();

    for(int i = 1;i <= n;i++){
      for(int j = 1;j <= n;j++){
        adj[i][j] = 0;
      }
    }
  }

  return 0;
}
