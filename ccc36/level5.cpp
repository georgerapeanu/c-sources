#include <bits/stdc++.h>

using namespace std;

pair<int,int> d[300];
vector<pair<int, int> > dir = {
  {-1, 0},
  {0, 1},
  {1, 0},
  {0, -1}
};
string dirChars = "URDL";
string opDirChars = "DLUR";

struct player_t{
  int x, y;
  int position;
  string movement;
  bool is_pacman;
  bool crashed;


  player_t(){
    x = y = 0;
    position = 0;
    movement = "";
    is_pacman = false;
    crashed = false;
  }

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

  void completePath(){
    int n = (int)movement.size();

    for(int i = n - 1;i >= 0;i--){
      for(int k = 0;k < (int)dirChars.size();k++){
        if(dirChars[k] == movement[i]){
          movement += opDirChars[k];
          break;
        }
      }
    }
  }
};

void update(const vector<string> &matrix, vector<player_t> &players){
  for(auto &player:players){
    if(player.position >= (int)player.movement.size()){
      player.position = 0;
    }
    char op = player.movement[player.position];
    player.position += 1;
    player.x += d[op].first;
    player.y += d[op].second;
    if(player.x < 0 || player.x >= (int)matrix.size() || player.y < 0 || player.y >= (int)matrix.size() || matrix[player.x][player.y] == 'W'){
      player.crashed = true;
      continue;
    }
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
  
  pair<int,int> coin = {0, 0};
  for(int i = 0;i < (int)matrix.size();i++){
    for(int j = 0;j < (int)matrix.size();j++){
      if(matrix[i][j] == 'C'){
        coin = {i, j};
        break;
      }
    }
  }

  player_t pacman;
  cin >> pacman.x >> pacman.y;
  pacman.x--;
  pacman.y--;
  pacman.is_pacman = true;


  vector<player_t> players = {};

  int m;
  cin >> m;

  for(int i = 0;i < m;i++){
    players.push_back(player_t());
    players.back().read();
    players.back().completePath();
  }

  vector<vector<vector<int> >> viz;
  viz.push_back(vector<vector<int> > (n, vector<int>(n,-1)));
  viz[0][pacman.x][pacman.y] = -2;


  while(viz.back()[coin.first][coin.second] == -1){
    vector<vector<int> > new_viz(n,vector<int>(n, -1));
    update(matrix, players);
    set<pair<int,int> > ghosts;

    for(auto player:players){
      ghosts.insert({player.x, player.y});
    }
    for(int i = 0;i < (int)matrix.size();i++){
      for(int j = 0;j < (int)matrix.size();j++){
        if(viz.back()[i][j] != -1){
          for(int k = 0;k < (int)dir.size();k++){
            int xx = i + dir[k].first;
            int yy = j + dir[k].second;
            if(xx < 0 || xx >= (int)matrix.size()){
              continue;
            }
            if(yy < 0 || yy >= (int)matrix.size()){
              continue;
            }
            if(matrix[xx][yy] == 'W' || ghosts.count({xx, yy})){
              continue;
            }
            new_viz[xx][yy] = k; 
          }
        }
      }
    }
    viz.push_back(new_viz);
  }

  int layer = (int)viz.size() - 1;
  int x = coin.first;
  int y = coin.second;

  string moves;

  while(layer >= 0){
    int xx = x - dir[viz[layer][x][y]].first;
    int yy = y - dir[viz[layer][x][y]].second;
    moves += dirChars[viz[layer][x][y]];
    x = xx;
    y = yy;
    layer--;
  }


  reverse(moves.begin(), moves.end());

  cout << moves << "\n";

  return 0;
}
