#include <bits/stdc++.h>

using namespace std;

const int NMAX = 3e5;

class FenwickTree{
  int n;
  vector<int> aib;

public:

  FenwickTree(int n){
    this->n = n;
    this->aib = vector<int>(n + 1,0);
  }

  void update(int pos,int value) {
    for(;pos <= n;pos += (-pos) & pos){
      aib[pos] += value;
    }
  }

  int query(int pos){
    int ans = 0;

    for(;pos;pos -= (-pos) & pos){
      ans += aib[pos];
    }

    return ans;
  }
};

class SegmentTree{

  struct node_t{
    int value;

    node_t(){
      value = 0;
    }

    node_t operator + (const node_t &other)const{
      node_t ans;
      ans.value = max(this->value,other.value);
      return ans;
    }
  };
  
  int n;
  vector<node_t> aint;

  void update(int nod,int st,int dr,int pos,int value){
    if(dr < pos || st > pos){
      return ;
    }

    if(st == dr){
      aint[nod].value = value;
      return ;
    }

    int mid = (st + dr) / 2;

    update(nod * 2,st,mid,pos,value);
    update(nod * 2 + 1,mid + 1,dr,pos,value);
    
    aint[nod] = aint[nod * 2] + aint[nod * 2 + 1];
  }

  int query(int nod,int st,int dr,int l,int r,int pos){
    if(r < st || l > dr || aint[nod].value < pos){
      return 0;
    }
    
    int mid = (st + dr) / 2;

    if(l <= st && dr <= r){
      if(st == dr){
        return st;
      }
      if(aint[nod * 2 + 1].value >= pos){
        return query(nod * 2 + 1,mid + 1,dr,l,r,pos);
      }else{
        return query(nod * 2,st,mid,l,r,pos);
      }
    }

    return max(query(nod * 2,st,mid,l,r,pos),query(nod * 2 + 1,mid + 1,dr,l,r,pos));
  }

public:

  SegmentTree(int n){
    this->n = n;
    aint = vector<node_t>(4 * n + 5,node_t());
  }

  void update(int pos,int value){
    update(1,1,n,pos,value);
  }

  int query(int pos){
    return query(1,1,n,1,pos,pos);
  }
};

int t;
int n;
vector<int> tree[2][NMAX + 5];
int last;
int l[NMAX + 5];
int r[NMAX + 5];
int id[NMAX + 5];

void liniarizare(int nod){
  l[nod] = ++last;
  id[last] = nod;
  for(auto it:tree[1][nod]){
    liniarizare(it);
  }
  r[nod] = last;
}

int ans = 0;

void add(int nod,FenwickTree &aib,SegmentTree &aint){
  ans += (aib.query(r[nod]) - aib.query(l[nod]) == 0); 
  int ancestor = id[aint.query(l[nod])];
  if(ancestor != 0){
    ans -= (aib.query(r[ancestor]) - aib.query(l[ancestor]) == 0);
  }


  aib.update(l[nod],1);
  aint.update(l[nod],r[nod]);
}

void remove(int nod,FenwickTree &aib,SegmentTree &aint){
  aib.update(l[nod],-1);
  aint.update(l[nod],0);

  ans -= (aib.query(r[nod]) - aib.query(l[nod]) == 0); 

  int ancestor = id[aint.query(l[nod])];

  if(ancestor != 0){
    ans += (aib.query(r[ancestor]) - aib.query(l[ancestor]) == 0);
  }
  
}

int query(){
  return ans;
}

int dfs(int nod,FenwickTree &aib,SegmentTree &aint){

  int ans = 0;

  add(nod,aib,aint);

  ans = max(ans,query());

  for(auto it:tree[0][nod]){
    ans = max(ans,dfs(it,aib,aint));
  }

  remove(nod,aib,aint);

  return ans;
}


int main(){
    
  scanf("%d",&t);

  while(t--){
    scanf("%d",&n);

    for(int h = 0;h < 2;h++){
      for(int i = 1;i <= n;i++){
        tree[h][i].clear();
      }
    }

    for(int h = 0;h < 2;h++){
      for(int i = 2;i <= n;i++){
        int father;
        scanf("%d",&father);
        tree[h][father].push_back(i);
      }
    }

    last = 0;
    liniarizare(1);

    FenwickTree aib(last);
    SegmentTree aint(last);

    printf("%d\n",dfs(1,aib,aint));
  }

  return 0;
}
