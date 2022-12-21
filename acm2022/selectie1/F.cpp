#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

const int dx[] = {-1, -1, 0, 1, 1, 1, 0, -1};
const int dy[] = {0, 1, 1, 1, 0, -1, -1, -1};

const int d2x[] = {-1, 0, 1, 0};
const int d2y[] = {0, 1, 0, -1};

int main(){

  int n, m, x, y;

  while(cin >> n >> m >> x >> y){
    if(n == 0 && m == 0 && x == 0 && y == 0){
      break;
    }
    x--;
    y--;

    vector<string> grid(n, "");

    for(int i = 0;i < n;i++){
      cin >> grid[i]; 
    }

    vector<vector<int> > visited(n, vector<int>(m, 0));

    vector<pair<int, int> > q;

    q.push_back(make_pair(x, y));
    visited[x][y] = 1;

    for(int i = 0; i < (int)q.size();i++){
      x = q[i].first;
      y = q[i].second;
      for(int k = 0;k < 8;k++){
        int xx = x + dx[k];
        int yy = y + dy[k];
        if(xx < 0 || xx >= n || yy < 0 || yy >= m || visited[xx][yy] || grid[xx][yy] == '.'){
          continue;
        }
        visited[xx][yy] = 1;
        q.push_back(make_pair(xx, yy));
      }
    }

    int answer = 0;

    for(int i = 0;i < (int)q.size();i++){
      int x = q[i].first;
      int y = q[i].second;
      for(int k = 0;k < 4;k++){
        int xx = x + d2x[k];
        int yy = y + d2y[k];
        if(xx < 0 || xx >= n || yy < 0 || yy >= m || !visited[xx][yy]){
          answer += 1;
        }
      }
    }

    cout << answer << "\n";

  }

  return 0;
}
