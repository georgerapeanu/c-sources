#include <bits/stdc++.h>

using namespace std;

pair<int,int> d[300];

int main(){

  d['L'] = {0, -1};
  d['R'] = {0, 1};
  d['U'] = {-1, 0};
  d['D'] = {1, 0};

  int n;
  cin >> n;

  vector<string> matrix(n);

  for(auto &it:matrix){
    cin >> it;
  }

  int x, y;
  cin >> x >> y;
  x--;y--;
  int m;
  cin >> m;
  string moves;
  cin >> moves;

  vector<vector<int> > viz(n, vector<int>(n, 0));

  viz[x][y] = 1;


  for(auto it:moves){
    x += d[it].first;
    y += d[it].second;
    viz[x][y] = 1;
  }

  int coins = 0;

  for(int i = 0;i < n;i++){
    for(int j = 0;j < n;j++){
      coins += (viz[i][j]) * (matrix[i][j] == 'C');  
    }
  }

  cout << coins;

  return 0;
}
