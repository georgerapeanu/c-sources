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
  long long sum;
  int previous_state;
  int move;

  state_t(){
    x = y = 0;
    sum = 0;
    previous_state = -1;
    move = 0;
  }

  bool operator < (const state_t &other)const {
    if(sum != other.sum){
      return sum < other.sum;
    }
    if(layer != other.layer){
      return layer < other.layer;
    }
    if(x != other.x){
      return x < other.x;
    }
//    if(y != other.y){
      return y < other.y;
//    }
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

map<pair<int,int>, int> coin_costs;

void compute_paths(const vector<string> &matrix, player_t &player, const player_t &pacman){
  vector<vector<int> > viz(matrix.size(), vector<int>(matrix.size(), -1));
  viz[player.x][player.y] = -2;
  vector<pair<int,int> > pos = {{player.x, player.y}};

  for(int i = 0;i < (int)pos.size(); i++){
    int x = pos[i].first;
    int y = pos[i].second;

    for(int k = 0;k < (int)dir.size();k++){
      int xx = x + dir[k].first;
      int yy = y + dir[k].second;
      if(xx < 0 || xx >= (int)matrix.size()){
        continue;
      }
      if(yy < 0 || yy >= (int)matrix.size()){
        continue;
      }
      if(viz[xx][yy] != -1){
        continue;
      }
      if(viz[xx][yy] == -1 && matrix[xx][yy] != 'W'){
        viz[xx][yy] = k;
        pos.push_back({xx,yy});
      }
    }
  }

    assert(viz[pacman.x][pacman.y] != -1);
    int x = pacman.x;
    int y = pacman.y;
    string moves = "";

    while(viz[x][y] != -2){
      int xx = x - dir[viz[x][y]].first;
      int yy = y - dir[viz[x][y]].second;
      moves += dirChars[viz[x][y]]; 
      x = xx;
      y = yy;
    }
    reverse(moves.begin(), moves.end());
    player.movement = moves;
    player.completePath();
    //cerr << "debug " << player.x << " " << player.y << " " << player.movement << "\n"; 
    player.position = 0;

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
  pacman.is_pacman = true;

 


  vector<player_t> players = {};

  int m;
  cin >> m;

  for(int i = 0;i < m;i++){
    players.push_back(player_t());
    players.back().read();
    players.back().completePath();
  }
  
  int cntCoins;
  cin >> cntCoins;
  for(int i = 0;i < cntCoins;i++){
    int x, y, cost;
    cin >> x >> y >> cost;
    x--;
    y--;
    coin_costs[{x,y}] = cost;
  }

  for(auto &player:players){
    compute_paths(matrix, player, pacman);
  }

  vector<set<pair<int, int>> > ghosts;
  set<state_t> visited;
  vector<state_t> states;
  ghosts.push_back(getGhostSet(players));
  states.push_back(state_t());
  states.back().layer = 0;
  states.back().x = pacman.x;
  states.back().y = pacman.y;
  states.back().sum = 0; // possible source of bugs if pacman starts on a coin;
  visited.insert(states.back());

  int answer_id = -1;
  long long answer_sum = 0;

  int limit;
  cin >> limit;

  //fuck my life i have to get all paths ok fuck --- maybe not ?????? 
  for(int i = 0; i < (int)states.size();i++){
    if(states[i].sum >= answer_sum){
      answer_id = i;
      answer_sum = states[i].sum;
    }
    if(states[i].layer >= limit){
      continue;
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
      
      state_t new_state;
      new_state.x = xx;
      new_state.y = yy;
      new_state.sum = states[i].sum + coin_costs[{xx, yy}];
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


  cout << answer_sum << "\n";
//  cerr << moves << "\n";

  return 0;
}
