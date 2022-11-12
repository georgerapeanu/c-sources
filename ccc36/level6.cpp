#include <bits/stdc++.h>

using namespace std;

pair<int,int> d[300];
vector<pair<int, int> > dir = {
  {1, 0},
  {0, -1},
  {0, 1},
  {-1, 0}
};
string dirChars = "DLRU";
string opDirChars = "URLD";

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

struct state_t{
  int layer;
  int x, y;
  int conf;
  int previous_state;
  int move;

  state_t(){
    x = y = 0;
    conf = 0;
    previous_state = -1;
    move = 0;
  }

  bool operator < (const state_t &other)const {
    if(layer != other.layer){
      return layer < other.layer;
    }
    if(x != other.x){
      return x < other.x;
    }
    if(y != other.y){
      return y < other.y;
    }
    return conf < other.conf;
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

set<pair<int,int> > getGhostSet(const vector<player_t> &players){
  set<pair<int, int> > answer;
  for(auto player:players){
    answer.insert({player.x, player.y});
  }
  return answer;
}

map<pair<int,int>, int> coin_ids;

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
 

  int last_coin = 0;
  for(int i = 0;i < (int)matrix.size();i++){
    for(int j = 0;j < (int)matrix.size();j++){
      if(matrix[i][j] == 'C'){
        coin_ids[{i,j}] = last_coin++;    
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

  vector<set<pair<int, int>> > ghosts;
  set<state_t> visited;
  vector<state_t> states;
  ghosts.push_back(getGhostSet(players));
  states.push_back(state_t());
  states.back().layer = 0;
  states.back().x = pacman.x;
  states.back().y = pacman.y;
  states.back().conf = 0; // possible source of bugs if pacman starts on a coin;
  visited.insert(states.back());

  int coin_count = coin_ids.size();

  int answer_id = -1;

  int limit;
  cin >> limit;

  //fuck my life i have to get all paths ok fuck --- maybe not ?????? 
  for(int i = 0; i < (int)states.size();i++){
    if(states[i].layer >= limit){
      continue;
    }
    if(states[i].conf == (1 << coin_count) - 1){
      answer_id = i;
      break;
    }
    while(states[i].layer + 1 >= (int)ghosts.size()){
      update(matrix, players);
      ghosts.push_back(getGhostSet(players)); 
    }

    for(int k = 0;k < (int)dir.size();k++){
      int xx = states[i].x + dir[k].first;
      int yy = states[i].y + dir[k].second;
      if(xx < 0 || xx >= (int)matrix.size()){
        continue;
      }
      if(yy < 0 || yy >= (int)matrix.size()){
        continue;
      }
      if(matrix[xx][yy] == 'W' || ghosts[states[i].layer + 1].count({xx, yy})){
        continue;
      }
      
      int conf = states[i].conf;
      if(coin_ids.count({xx, yy})){
        conf |= (1 << coin_ids[{xx,yy}]); 
      }
      state_t new_state;
      new_state.x = xx;
      new_state.y = yy;
      new_state.conf = conf;
      new_state.layer = states[i].layer + 1;
      new_state.previous_state = i;
      new_state.move = k;
      if(visited.count(new_state)){
        continue;
      }
      visited.insert(new_state);
      states.push_back(new_state);
    }
  }

  string moves;

  while(answer_id > 0){
    moves += dirChars[states[answer_id].move];
    answer_id = states[answer_id].previous_state;
  }

  reverse(moves.begin(), moves.end());

  cout << moves << "\n";

  return 0;
}
