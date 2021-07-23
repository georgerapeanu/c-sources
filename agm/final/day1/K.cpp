#include <bits/stdc++.h>

using namespace std;

const int NMAX = 1e5;
const int LGMAX = 20;

int n,m,q;
vector<int> graph[NMAX + 5];
int last_id;
int id[NMAX + 5];
int low[NMAX + 5];
bool viz[NMAX + 5];
int values[NMAX + 5];
vector<int> tree[NMAX + 5];
vector<int> nodes[NMAX + 5];

void dfs(int nod,int tata){
  viz[nod] = true;
  low[nod] = id[nod] = ++last_id;
  for(auto it:graph[nod]){
    if(it == tata){
      continue;
    }
    if(!viz[it]){
      dfs(it,nod);
    }
    low[nod] = min(low[nod],low[it]);
  }
}

struct node_t{
  node_t *sons[2];
  int cnt;

  node_t(){
    cnt = 0;
    memset(sons,0,sizeof(sons));
  }
};

vector<node_t*> garbageCollector;

node_t* ins(node_t *root,int value,int pos){
  node_t *node = new node_t();
  garbageCollector.push_back(node);
  node->cnt = root->cnt;
  node->cnt++;
  for(int i = 0;i < 2;i++){
    node->sons[i] = root->sons[i];
  }
  if(pos < 0){
    return node;
  }

  if(node->sons[(value >> pos) & 1] == NULL){
    node->sons[(value >> pos) & 1] = new node_t();
    garbageCollector.push_back(node->sons[(value >> pos) & 1]);
  }

  node->sons[(value >> pos) & 1] = ins(node->sons[(value >> pos) & 1],value,pos - 1);
  return node;
}

int lvl[NMAX + 5];
int father[LGMAX + 1][NMAX + 1];
node_t* roots[NMAX + 5];

void build_tree(int nod,int tata){
  lvl[nod] = 1 + lvl[tata];
  father[0][nod] = tata;
  roots[nod] = roots[tata];
  for(auto it:nodes[nod]){
    roots[nod] = ins(roots[nod],values[it],LGMAX);
  }
  for(auto it:tree[nod]){
    if(it == tata){
      continue;
    }
    build_tree(it,nod);  
  }
}

int lca(int x,int y){
  if(lvl[x] > lvl[y]){
    swap(x,y);
  }
  
  for(int h = LGMAX;h >= 0;h--){
    if((lvl[y] - lvl[x]) >> h){
      y = father[h][y];
    }
  }

  if(x == y){
    return x;
  }

  for(int h = LGMAX;h >= 0;h--){
    if(father[h][x] != father[h][y]){
      x = father[h][x];
      y = father[h][y];
    }
  }

  return father[0][x];
}

node_t* getSon(node_t* root,int b){
  if(root == NULL){
    return NULL;
  }
  return root->sons[b];
}

int get(node_t* root){
  if(root == NULL){
    return 0;
  }
  return root->cnt;
}


int query(node_t* x,node_t* y,node_t* w,node_t* father,int v,int k,int pos){
  if(pos == -1){
    if(k <= get(x) + get(y) - get(w) - get(father)){
      return 0;
    }
    return -1;
  }
  int b = ((v >> pos) & 1);
  int tmp = (get(getSon(x,b)) + get(getSon(y,b)) - get(getSon(father,b)) - get(getSon(w,b)));
  if(tmp >= k){
    int ans = query(getSon(x,b),getSon(y,b),getSon(w,b),getSon(father,b),v,k,pos - 1);
    if(ans == -1){
      return -1;
    }
    return (ans | (0 << pos));
  }else{
    int ans = query(getSon(x,!b),getSon(y,!b),getSon(w,!b),getSon(father,!b),v,k - tmp,pos - 1);
    if(ans == -1){
      return -1;
    }
    return (ans | ((1) << pos));
  }
}

int main(){

  scanf("%d %d %d",&n,&m,&q);

  for(int i = 1;i <= n;i++){
    scanf("%d",&values[i]);
  }

  for(int i = 1;i <= m;i++){
    int x,y;
    scanf("%d %d",&x,&y);
    graph[x].push_back(y);
    graph[y].push_back(x);
  }

  dfs(1,0);

  for(int i = 1;i <= n;i++){
    nodes[low[i]].push_back(i);
    for(auto it:graph[i]){
      if(low[it] != low[i]){
        tree[low[i]].push_back(low[it]);
        tree[low[it]].push_back(low[i]);
      }
    }
  }

  for(int i = 1;i <= n;i++){
    sort(tree[i].begin(),tree[i].end());
    tree[i].resize(unique(tree[i].begin(),tree[i].end()) - tree[i].begin());
  }

  roots[0] = new node_t();
  garbageCollector.push_back(roots[0]);
  build_tree(1,0);

  for(int h = 1;h <= LGMAX;h++){
    for(int i = 1;i <= n;i++){
      father[h][i] = father[h - 1][father[h - 1][i]];
    }
  }

  //for(int i = 1;i <= n;i++){
  //  printf("deb %d %d\n",i,low[i]);
  //}

  while(q--){
    int x,y,v,k;
    scanf("%d %d %d %d",&x,&y,&v,&k);
  //  printf("deb %d %d %d %d\n",x,y,v,k);
    x = low[x];
    y = low[y];
    int w = lca(x,y);
  //  printf("query %d %d %d %d %d %d\n",x,y,w,father[0][w],v,k);
    printf("%d\n",query(roots[x],roots[y],roots[w],roots[father[0][w]],v,k,LGMAX));
  }

  for(auto it:garbageCollector){
    delete it;
  }

  return 0;
}
