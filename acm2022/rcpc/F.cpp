#include <bits/stdc++.h>

using namespace std;

const int PERIOD = 7 * 5 * 3 * 4 * 2;
//const int PERIOD = 10;

char line[100];

int dx[] = {-1, 0, 1, 0, 0};
int dy[] = {0, 1, 0, -1, 0};

vector<vector<bool> > generate_map(int level, const vector<string> &initial, const vector<vector<pair<int, int> > > &guards){
  vector<vector<bool> > answer(initial.size(), vector<bool>(initial[0].size(), false));

  for(int i = 0;i < (int)initial.size();i++){
    for(int j = 0;j < (int)initial[i].size();j++){
      if(initial[i][j] == '#'){
        answer[i][j] = true;
      }
    }
  }

  for(const auto &guard:guards){
    int x = guard[level].first;
    int y = guard[level].second;
    for(int k = 0;k < 4;k++){
      for(int l = 0;;l++){
        int xx = x + dx[k] * l;
        int yy = y + dy[k] * l;
        if(xx < 0 || xx >= (int)initial.size() || yy < 0 || yy >= (int)initial[xx].size() || initial[xx][yy] == '#'){
          break;
        }
        answer[xx][yy] = true;
      }
    }
  }
  return answer;
}

int main(){

  int n, m;

  scanf("%d %d\n", &n, &m);

  int start_x, start_y;
  int end_x, end_y;

  scanf("(%d %d) (%d %d)\n", &start_x, &start_y, &end_x, &end_y);

  start_x--;
  start_y--;
  end_x--;
  end_y--;

  vector<string> initial(n, "");
  
  for(int i = 0;i < n;i++){
    fgets(line, 100, stdin);
    for(int j = 0;j < m;j++){
      initial[i] += line[j];
    }
  }

  int g;

  scanf("%d", &g);

  vector<vector<pair<int, int>> > guards;

  for(int i = 0;i < g;i++){
    int len;
    scanf("%d ", &len);
    vector<pair<int,int> > initial;
    for(int i = 1;i <= len;i++){
      int x, y;
      scanf("(%d %d) ", &x, &y);
      x--;
      y--;
      initial.push_back({x, y});
    }
    vector<pair<int,int>> full;
    int current = 0;
    int sgn = 1;

    while((int)full.size() < PERIOD){
      full.push_back(initial[current]);
      current += sgn;
      if(current >= (int)initial.size() || current < 0){
        sgn *= -1;
        current += sgn * 2;
        if((int)initial.size() == 1){
          current = 0;
        }
      }
    }
    guards.push_back(full);
    scanf("\n");
  }

  vector<vector<vector<bool> > > matrix;

  for(int i = 0;i < PERIOD;i++){
    matrix.push_back(generate_map(i, initial, guards));
/*    for(int i = 0;i < n;i++){
      for(int j = 0;j < m;j++){
        printf("%d", matrix.back()[i][j] ? 1:0);
      }
      printf("\n");
    }
    printf("\n");*/
  }
  
  vector<vector<vector<int> > > viz(matrix.size(), vector<vector<int> >(matrix[0].size(), vector<int>(matrix[0][0].size(), -1)));

  vector<pair<int, pair <int, int> > > q;
  if(matrix[0][start_x][start_y] == false){
    viz[0][start_x][start_y] = 0;

    q.push_back({0, {start_x, start_y}});
  }

  for(int i = 0;i < (int)q.size();i++){
    int level = q[i].first;
    int x = q[i].second.first;
    int y = q[i].second.second;


    if(x == end_x && y == end_y){
      printf("%d\n", viz[level][x][y]);
      return 0;
    }

    for(int k = 0;k < 5;k++){
      int ll = (level + 1) % PERIOD;
      int xx = x + dx[k];
      int yy = y + dy[k];
      if(xx < 0 || xx >= (int)initial.size() || yy < 0 || yy >= (int)initial[xx].size() || viz[ll][xx][yy] != -1){
        continue;
      }
      if(matrix[ll][xx][yy] && (xx != end_x || yy != end_y)){
        continue;   
      }
      viz[ll][xx][yy] = viz[level][x][y] + 1;
      q.push_back({ll,{xx,yy}});
    }
  }

  printf("IMPOSSIBLE\n");


  return 0;
}
