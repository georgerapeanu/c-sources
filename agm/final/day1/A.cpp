#include <bits/stdc++.h>

using namespace std;

const int NMAX = 1e5;
const int MOD1 = 1e9 + 7;
const int MOD2 = 1e9 + 9;
const int BASE = 31;

int pw1[NMAX + 5];
int pw2[NMAX + 5];

struct hash_t{
  int h1;
  int h2;
  int len;

  hash_t(){
    h1 = h2 = len = 0;
  }

  hash_t(char c){
    h1 = c - 'a';
    h2 = c - 'a';
    len = 1;
  }

  hash_t operator + (const hash_t &other)const{
    hash_t ans;
    ans.h1 = (1LL * this->h1 * pw1[other.len] + other.h1) % MOD1;
    ans.h2 = (1LL * this->h2 * pw2[other.len] + other.h2) % MOD2;
    ans.len = this->len + other.len;
    return ans;
  }

  bool operator < (const hash_t &other)const{
    if(len != other.len){
      return len < other.len;
    }
    if(h1 != other.h1){
      return h1 < other.h1;
    }
    return h2 < other.h2;
  }

};

int n;
string s;
string t;
int weight[NMAX + 5];
bool inCentroid[NMAX + 5];

vector<int> graph[NMAX + 5];

map<hash_t,int> suffT;
hash_t prefT[NMAX + 5];

void predfs(int nod,int tata){
  weight[nod] = 1;
  for(auto it:graph[nod]){
    if(it == tata || inCentroid[it]){
      continue;
    }
    predfs(it,nod);
    weight[nod] += weight[it];
  }
}



void dfs(int nod,int tata,int mode,map<hash_t,int> &fr,hash_t suff,hash_t pref,long long &ans){
  suff = suff + hash_t(t[nod]);
  pref = hash_t(t[nod]) + pref;

  if(mode != 0){
    fr[pref] += mode;
  }else{
    if(suffT.count(suff)){
      ans += (fr[prefT[suffT[suff] - 1]]);
    }
  }

  for(auto it:graph[nod]){
    if(it == tata || inCentroid[it]){
      continue;
    }
    dfs(it,nod,mode,fr,suff,pref,ans);
  }
}

map<hash_t,int> fr;
void centroid(int nod,long long &ans){
  predfs(nod,0);

  int tata = 0;
  int root = nod;

  while(true){
    int bigChild = -1;
    for(auto it:graph[root]){
      if(it == tata || inCentroid[it]){
        continue;
      }
      if(bigChild == -1 || weight[it] > weight[bigChild]){
        bigChild = it;
      }
    }
    if(weight[bigChild] * 2 > weight[nod]){
      tata = root;
      root = bigChild;
    }else{
      break;
    }
  }
 
  inCentroid[root] = true;
  fr.clear();
  fr[hash_t()]++;
  for(auto it:graph[root]){
    if(inCentroid[it] == true){
      continue;
    }
    dfs(it,root,1,fr,hash_t(),hash_t(),ans);
  }
  for(auto it:graph[root]){
    if(inCentroid[it] == false){
      dfs(it,root,-1,fr,hash_t(),hash_t(),ans);
      dfs(it,root,0,fr,hash_t(t[root]),hash_t(t[root]),ans);
      dfs(it,root,1,fr,hash_t(),hash_t(),ans);
    }
  }

  for(auto it:graph[root]){
    if(inCentroid[it] == false){
      centroid(it,ans);
    }
  }
}

int main(){

  cin.sync_with_stdio(false);cin.tie(0);
  cout.sync_with_stdio(false);cout.tie(0);

  pw1[0] = pw2[0] = 1;

  for(int i = 1;i <= NMAX;i++){
    pw1[i] = 1LL * pw1[i - 1] * BASE % MOD1;
    pw2[i] = 1LL * pw2[i - 1] * BASE % MOD2;
  }

  cin >> n;
  cin >> s;
  cin >> t;
  s = " " + s;
  t = " " + t;

  if(s.size() == 1){
    int ans = 0;
    for(auto it:t){
      ans += (it == s[0]);
    }
    cout << ans;
    return 0;
  }

  for(int i = 1; i < n;i++){
    int x,y;
    cin >> x >> y;
    graph[x].push_back(y);
    graph[y].push_back(x);
  }

  prefT[0] = hash_t();

  for(int i = 1;i < (int)s.size();i++){
    prefT[i] = prefT[i - 1] + hash_t(s[i]);
  }

  hash_t tmp;
  for(int i = (int)s.size() - 1;i > 0;i--){
    tmp = hash_t(s[i]) + tmp;
    suffT[tmp] = i;
  }

  long long ans = 0;

  centroid(1,ans);

  cout << ans;

  return 0;
}
