#include <bits/stdc++.h>

using namespace std;

int n,m;
int v[1005][1005];
bool in_ops[1005][1005];

int get_color(int i,int j){
  if(1 <= i && 1 <= j && i < n && j < m){
    vector<int> values = {};
    for(int dx = 0;dx < 2;dx++){
      for(int dy = 0;dy < 2;dy++){
        values.push_back(v[i + dx][j + dy]);
      }
    }
    sort(values.begin(),values.end());
    for(int i = 0;i < (int)values.size();i++){
      if(values[i] == -1){
        continue;
      }
      if(i > 0 && values[i - 1] != -1 && values[i] != values[i - 1]){
        return -1;
      }
    }
    return values.back();
  }
  return -1;
}

int main(){
  
  scanf("%d %d", &n, &m);

  vector<pair<pair<int,int>,int> > ops;

  for(int i = 1;i <= n;i++){
    for(int j = 1;j <= m;j++){
      scanf("%d", &v[i][j]);
    }
  }

  
  for(int i = 1;i <= n;i++){
    for(int j = 1;j <= m;j++){
      if(get_color(i, j) != -1){
        ops.push_back({{i, j}, get_color(i, j)});
        in_ops[i][j] = true;
      }
    }
  }

  for(int i = 0;i < (int)ops.size();i++){
    pair<pair<int,int>,int> op = ops[i];
    int x = op.first.first;
    int y = op.first.second;
    int c = op.second;
    for(int dx = 0;dx < 2;dx++){
      for(int dy = 0;dy < 2;dy++){
        v[x + dx][y + dy] = -1;
      }
    }
    for(int dx = -1;dx <= 1;dx++){
      for(int dy = -1;dy <= 1;dy++){
        if(in_ops[x + dx][y + dy] == false && get_color(x + dx, y + dy) != -1){
          in_ops[x + dx][y + dy] = true;
          ops.push_back({{x + dx, y + dy}, get_color(x + dx, y + dy)});
        }
      }
    }
  }

  for(int i = 1;i <= n;i++){
    for(int j = 1;j <= m;j++){
      if(v[i][j] != -1){
        printf("-1");
        return 0;
      }
    }
  }
  
  reverse(ops.begin(), ops.end());
  
  printf("%d\n", (int)ops.size());
  for(auto it:ops){
    printf("%d %d %d\n", it.first.first, it.first.second, it.second);
  }

    return 0;
}
