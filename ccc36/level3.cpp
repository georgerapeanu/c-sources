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
  pacman.read();
  pacman.is_pacman = true;


  vector<player_t> players = {pacman};

  int m;
  cin >> m;

  for(int i = 0;i < m;i++){
    players.push_back(player_t());
    players.back().read();
  }

  vector<vector<int> > viz(n, vector<int>(n, 0));

  while(!players[0].crashed && players[0].position < (int)players[0].movement.size()){
    update(matrix, players, viz); 
  }

  int coins = 0;

  for(int i = 0;i < n;i++){
    for(int j = 0;j < n;j++){
      coins += (matrix[i][j] == 'C') * viz[i][j];
    }
  }

  cout << coins << " " << (!players[0].crashed ? "YES":"NO");
       

  return 0;
}
