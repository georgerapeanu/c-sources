#include <bits/stdc++.h>

using namespace std;

int main(){

  int t;

  scanf("%d", &t);

  while(t--){
    int n;
    scanf("%d", &n);

    vector<int> b(n + 1, 0);
    int __left = 0, __right = n;
    for(int i = 1;i <= n;i++){
      scanf("%d", &b[i]);
      if(i < b[i]){
       __right = min(__right, b[i] - 1);
       __left = max(__left, i);
      }else{
        __right = min(__right, i - 1);
        __left = max(__left, b[i]);
      }
    }
    int k = __left;

    vector<vector<int>> graph(n + 2, vector<int>());
  
    for(int i = 1;i <= n;i++){
      graph[b[i]].push_back(i);
    }
    int root = 0;
    if(graph[n + 1].size() > 0){
      root = n + 1;
    }
    vector<int> nodes = {root};

    for(int i = 0;i < (int)nodes.size();i++){
      for(auto it:graph[nodes[i]]){
        if((int)graph[it].size() == 0){
          nodes.push_back(it);
        }
      }
      for(auto it:graph[nodes[i]]){
        if((int)graph[it].size() != 0){
          nodes.push_back(it);
        }
      }
    }
    printf("%d\n", k);
    for(int i = 1;i < (int)nodes.size();i++){
      printf("%d ", nodes[i]);
    }
    printf("\n");
  }

  return 0;
}
