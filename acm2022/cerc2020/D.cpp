#include <bits/stdc++.h>

using namespace std;
map<char, vector<pair<int, int> > > directions; 

struct answer_t{
  int from_x;
  int from_y;
  int to_x;
  int to_y;
};

vector<answer_t> getWalk(const vector<string>& matrix, const vector<pair<int, int> > &directions, int x, int y){
  int n = matrix.size();
  vector<vector<int> > viz(n, vector<int>(n, 0)); 
  vector<answer_t> answer;
  answer.push_back({-1, -1, x, y}); 
  viz[x][y] = true;

  for(int i = 0; i < (int)answer.size();i++){
    x = answer[i].to_x;
    y = answer[i].to_y;
    for(auto it:directions){
      int xx = x + it.first;
      int yy = y + it.second;
      if(xx < 0 || xx >= n || yy < 0 || yy >= n || matrix[xx][yy] != matrix[x][y] || viz[xx][yy]){
        continue;
      }
      answer.push_back({x, y, xx, yy});
      viz[xx][yy] = true;
    }
  }
  reverse(answer.begin(), answer.end());
  answer.pop_back();
  return answer;
}

int main(){

  int n;
  char stuff;
  scanf("%d %c\n",&n, &stuff);

  directions['K'] = {};
  directions['Q'] = {};
  directions['R'] = {};
  directions['B'] = {};
  directions['N'] = {};

  for(int i = -1;i <= 1;i++){
    for(int j = -1;j <= 1;j++){
      directions['K'].push_back({i, j});
    }
  }

  for(int i = 1;i <= n;i++){
    for(int j = -1;j <= 1;j++){
      for(int k = -1;k <= 1;k++){
        directions['Q'].push_back({i * j, i * k});
        if(((j == 0) + (k == 0)) == 1){
          directions['R'].push_back({i * j, i * k});
        }
        if(((j == 0) + (k == 0)) == 0){
          directions['B'].push_back({i * j, i * k});
        }
      }
    }
  }

  for(int i = -2;i <= 2;i++){
    for(int j = -2;j <= 2;j++){
      if((abs(i) == 1 && abs(j) == 2) || (abs(i) == 2 && abs(j) == 1)){
        directions['N'].push_back({i, j});
      }
    }
  }

  int count = 0;
  vector<string> matrix(n);

  for(auto &it:matrix){
    cin >> it;
    for(auto &it2:it){
      count += (it2 == stuff);
    }
  }


  vector<answer_t> answer;
  
  for(int i = 0;i < n;i++){
    for(int j = 0;j < n;j++){
      if(matrix[i][j] == stuff){
        answer = getWalk(matrix, directions[stuff], i, j);
        goto done;
      }
    }
  }
done:;

  if((int)answer.size() == count - 1){
    printf("YES\n"); 
    for(auto it:answer){
      printf("%d %d %d %d\n", it.to_x + 1, it.to_y + 1, it.from_x + 1, it.from_y + 1); 
    }
  } else {
    printf("NO\n");
  }

  return 0;
}
