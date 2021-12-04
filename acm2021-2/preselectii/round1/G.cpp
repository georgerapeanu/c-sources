#include <bits/stdc++.h>

using namespace std;

const int SIGMA = 'z' - 'a' + 1;
const int NMAX = 1e5;

struct node_t{
  node_t *sons[SIGMA];
  int l;
  int r;
  vector<int> ids;

  node_t(){
    memset(sons,0,sizeof(sons));
    l = r = 0;
    ids = vector<int>();
  }
};

void ins(node_t *root,const string &s,int id,int pos){
  if(pos >= (int)s.size()){
    root->ids.push_back(id);
    return;
  }

  if(root->sons[s[pos] - 'a'] == NULL){
    root->sons[s[pos] - 'a'] = new node_t();
  }

  ins(root->sons[s[pos] - 'a'],s,id,pos + 1);
}

void liniarizare(node_t *root,vector<int> &order){
  root->l = order.size();
  for(auto it:root->ids){
    order.push_back(it);
  }
  for(int i = 0;i < SIGMA;i++){
    if(root->sons[i] == NULL){
      continue;
    }
    liniarizare(root->sons[i],order);
  }
  root->r = ((int)order.size()) - 1;
}

pair<int,int> fetchInterval(node_t *root,const string &s,int pos){
  if(pos >= (int)s.size()){
    return {root->l,root->r};
  }
  
  if(root->sons[s[pos] - 'a'] == NULL){
    return {-1,-1};
  }else{
    return fetchInterval(root->sons[s[pos] - 'a'],s,pos + 1);
  }
}

struct query_t{
  int sgn;
  int i;
  int l,r;
  int id;

  bool operator < (const query_t &other)const{
    if(i != other.i){
      return i < other.i;
    }
    return id < other.id;
  }
};



vector<query_t> queries;

int n,m;
string s;

int aib[NMAX + 5];

void update(int pos,int value){
  pos += 1;
  for(;pos <= n;pos += (-pos) & pos){
    aib[pos] += value;
  }
}

int query(int pos){
  int ans = 0;
  pos += 1;
  for(;pos;pos -= (-pos) & pos){
    ans += aib[pos];
  }
  return ans;
}

int main(){
    
    cin >> n >> m;

    vector<int> ans(m,0);

    node_t *r1,*r2;
    r1 = new node_t();
    r2 = new node_t();

    for(int i = 1;i <= n;i++){
      cin >> s;
      ins(r1,s,i - 1,0);
      reverse(s.begin(),s.end());
      ins(r2,s,i - 1,0);
    }

    vector<int> lin1,lin2;

    liniarizare(r1,lin1);
    liniarizare(r2,lin2);

    vector<int> inv2(n);

    for(int i = 0;i < (int)lin2.size();i++){
      inv2[lin2[i]] = i;
    }

    for(int i = 1;i <= m;i++){
      cin >> s;
      string pref,suff;
      pref = "";
      suff = "";
      for(int i = 0;s[i] != '*';i++){
        pref += s[i];
      }
      for(int i = (int)s.size() - 1;s[i] != '*';i--){
        suff += s[i];
      }
      pair<int,int> a = fetchInterval(r1,pref,0);
      pair<int,int> b = fetchInterval(r2,suff,0);

      if(a != make_pair(-1,-1) && b != make_pair(-1,-1)){
        queries.push_back({-1,a.first - 1,b.first,b.second,i - 1});
        queries.push_back({1,a.second,b.first,b.second,i - 1});
      }
    }

    sort(queries.begin(),queries.end());

    int last = -1;

    for(auto it:queries){
      while(last < it.i){
        last++;
        update(inv2[lin1[last]],1);
      }
      ans[it.id] += it.sgn * (query(it.r) - query(it.l - 1));
    }

    for(auto it:ans){
      printf("%d\n",it);
    }

    return 0;
}
