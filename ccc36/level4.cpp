#include <bits/stdc++.h>

using namespace std;

pair<int,int> d[300];

struct player_t{
  int x, y;
  int position;
  string movement;
  bool is_pacman;
  bool crashed;

  void read(){
    int _;
    cin >> x >> y;
    x--;y--;
    cin >> _;
    cin >> movement;
    position = 0;
    crashed = false;
    is_pacman = false;
  }

  player_t(){
    x = y = 0;
    position = 0;
    movement = "";
    is_pacman = false;
    crashed = false;
  }
};

void update(const vector<string> &matrix, vector<player_t> &players, vector<vector<int> > &viz){
  for(auto &player:players){
    if(player.crashed || player.position >= (int)player.movement.size()){
      continue;
    }
    char op = player.movement[player.position++];
    player.x += d[op].first;
    player.y += d[op].second;
    if(player.x < 0 || player.x >= (int)matrix.size() || player.y < 0 || player.y >= (int)matrix.size() || matrix[player.x][player.y] == 'W'){
      player.crashed = true;
      continue;
    }
  }

  for(int i = 1;i < (int)players.size();i++){
    if(players[0].x == players[i].x && players[0].y == players[i].y){
      players[0].crashed = true;
    }
  }

  if(players[0].crashed == false){
      viz[players[0].x][players[0].y] = true;
  }

}

vector<pair<int, int> > dir = {
  {-1, 0},
  {0, 1},
  {1, 0},
  {0, -1}
};
string dirChars = "URDL";
string opDirChars = "DLUR";

void dfs(player_t &pacman,const vector<string> &matrix, vector<vector<int>> &viz) {
    viz[pacman.x][pacman.y] = true;

    for(int k = 0;k < (int)dir.size();k++){
      pair<int,int> it = dir[k];
      int xx = pacman.x + it.first;
      int yy = pacman.y + it.second;

      if(xx < 0 || xx >= (int)matrix.size()){
        continue;
      }
      if(yy < 0 || yy >= (int)matrix.size()){
        continue;
      }
      if(viz[xx][yy] || matrix[xx][yy] == 'G' || matrix[xx][yy] == 'W'){
        continue;
      }
      pacman.movement += dirChars[k];
      pacman.x += dir[k].first;
      pacman.y += dir[k].second;
      dfs(pacman, matrix, viz);
      pacman.x -= dir[k].first;
      pacman.y -= dir[k].second;
      pacman.movement += opDirChars[k];
    }
}

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

  player_t pacman;
  cin >> pacman.x >> pacman.y;
  pacman.x--;
  pacman.y--;
  vector<vector<int> > viz(n, vector<int>(n, 0));

  dfs(pacman, matrix, viz);
  
  cout << pacman.movement;

  return 0;
}
