#include <bits/stdc++.h>

using namespace std;

const int NMAX = 1e5;
const int MMAX = 1e5;

const int NODES_MAX = 2 * NMAX + 5;

vector<int> graph[NODES_MAX];
map<string,int> to_norm;

int n,m;
vector<string> essay;

int last_norm;
int last_id;
int low[NODES_MAX];
int id[NODES_MAX];
int st[NODES_MAX];
int ctc[NODES_MAX];
int last_ctc;
int len_st;
bool inst[NODES_MAX];
pair<int,int> cost[NODES_MAX];
pair<int,int> ctc_cost[NODES_MAX];
vector<int> compo[NODES_MAX];

int access(const string &s){
  if(!to_norm.count(s)){
    to_norm[s] = ++last_norm;
  }
  return to_norm[s];
}


void dfs(int nod){
  inst[nod] = true;
  st[++len_st] = nod;
  low[nod] = id[nod] = ++last_id;

  for(auto it:graph[nod]){
    if(id[it] == 0){
      dfs(it);
    }
    if(inst[it]){
      low[nod] = min(low[nod],low[it]);
    }
  }

  if(low[nod] == id[nod]){
    ++last_ctc;

    while(st[len_st] != nod){
      ctc[st[len_st]] = last_ctc;
      inst[st[len_st]] = false;
      len_st--;
    }
    ctc[st[len_st]] = last_ctc;
    inst[st[len_st]] = false;
    len_st--;
  }
}

pair<int,int> get_cost(const string &s){
  int r_count = 0;

  for(auto &it:s){
    r_count += (it == 'r');
  }

  return {r_count,s.size()};
}

string to_lower(string s){
  for(auto &it:s){
    if('A' <= it && it <= 'Z'){
      it += 'a' - 'A';
    }
  }

  return s;
}

pair<int,int> best_deal(const string &s){
  if(!to_norm.count(s)){
    return get_cost(s);
  }
  return ctc_cost[ctc[access(s)]];
}



int main(){

  cin >> n;

  essay = vector<string>(n);

  for(auto &it:essay){
    cin >> it;
    it = to_lower(it);
  }

  cin >> m;

  for(int i = 1;i <= m;i++){
    string x,y;
    cin >> x >> y;
    x = to_lower(x);
    y = to_lower(y);
    graph[access(x)].push_back(access(y));
    cost[access(x)] = get_cost(x);
    cost[access(y)] = get_cost(y);
  }


  for(int i = 1;i <= last_norm;i++){
    if(id[i] == 0){
      dfs(i);
    }
  }
  
  for(int i = 1;i <= last_ctc;i++){
    ctc_cost[i] = {1e9,1e9};
  }

  for(int i = 1;i <= last_norm;i++){
    compo[ctc[i]].push_back(i);
    ctc_cost[ctc[i]] = min(ctc_cost[ctc[i]],cost[i]);
  }

  for(int i = 1;i <= last_ctc;i++){
    for(auto nod:compo[i]){
      for(auto it:graph[nod]){
        ctc_cost[i] = min(ctc_cost[i],ctc_cost[ctc[it]]);
      }
    }
  }

  pair<int,long long> ans = {0,0};

  for(auto it:essay){
    pair<int,int> tmp = best_deal(it);
    ans.first += tmp.first;
    ans.second += tmp.second;
  }

  cout << ans.first << " " << ans.second << "\n";


  return 0;
}
