#include <bits/stdc++.h>

using namespace std;


void dfs(int nod, vector<int> &viz, vector<int> &current_positions, const vector<int> &lengths){
  viz[nod] = true;
  current_positions.push_back(nod);
  for(auto it:lengths){
    if(nod - it >= 0 && viz[nod - it] == false){
      dfs(nod - it, viz, current_positions, lengths); 
    }
    if(nod + it < (int)viz.size() && viz[nod + it] == false){
      dfs(nod + it, viz, current_positions, lengths); 
    }
  }
}

int main(){
  int n, k;
  scanf("%d %d", &n, &k);
  assert(1 <= n && n <= 100);

  vector<int> perm(n, 0);
  vector<int> lengths(k, 0);

  for(auto &it:perm){
    scanf("%d", &it);
  }
  
  for(auto &it:lengths){
    scanf("%d", &it);
  }

  vector<int> viz(n, 0);
  vector<int> current_positions;
  vector<int> current_values;
  vector<int> ans(n, 0);

  for(int i = 0;i < n;i++){
    if(viz[i] == false){
      current_positions.clear();
      current_values.clear();
      dfs(i, viz, current_positions, lengths);

      for(auto it:current_positions){
        current_values.push_back(perm[it]);
      }

      sort(current_positions.begin(),current_positions.end());
      sort(current_values.begin(),current_values.end());

      for(int i = 0;i < (int)current_positions.size();i++){
        ans[current_positions[i]] = current_values[i];
      }
    }
  }

  for(auto it:ans){
    printf("%d ", it);
  }

  printf("\n");

  return 0;
}
