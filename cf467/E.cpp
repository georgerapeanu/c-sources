#include <bits/stdc++.h>

using namespace std;

const int NMAX = 5e5;

int n;
int a[NMAX + 5];
map<int,int> last;
int father[NMAX + 5];
int bst[NMAX + 5];
int bst2[NMAX + 5];
int dp[NMAX + 5];
int ant[NMAX + 5];

class SegmentTree{
  int n;
  vector<int> aint;

  void update(int nod,int st,int dr,int pos,int val){
    if(dr < pos || st > pos){
      return ;
    }
    if(st == dr){
      aint[nod] = val;
      return ;
    }
    int mid = (st + dr) / 2;

    update(nod * 2,st,mid,pos,val);
    update(nod * 2 + 1,mid + 1,dr,pos,val);

    aint[nod] = max(aint[nod * 2],aint[nod * 2 + 1]);
  }

  int query(int nod,int st,int dr,int l,int r){
    if(r < st || l > dr){
      return 0;
    }
    
    if(l <= st && dr <= r){
      return aint[nod];
    }

    int mid = (st + dr) / 2;

    return max(query(nod * 2,st,mid,l,r),query(nod * 2 + 1,mid + 1,dr,l,r));
  }

public:

  SegmentTree(int n){
    this->n = n;
    this->aint = vector<int>(4 * n + 5);
  }

  void update(int pos,int val){
    this->update(1,1,this->n,pos,val);
  }

  int query(int l,int r){
    return query(1,1,this->n,l,r);
  }
};

int main(){

  scanf("%d",&n);

  SegmentTree aint(n);

  vector<pair<int,int> > stuff;

  for(int i = 1;i <= n;i++){
    scanf("%d",&a[i]);
    father[i] = last[a[i]];

    if(father[father[father[i]]]){
      bst2[i] = father[father[father[i]]];
    }

    if(last.count(a[i])){
      stuff.push_back({last[a[i]],i});
    }

    last[a[i]] = i;
  }

  sort(stuff.begin(),stuff.end());

  for(auto it:stuff){
      bst[it.second] = aint.query(it.first + 1,it.second);
      aint.update(it.second,it.first);
  }

  for(int i = 1;i <= n;i++){
    dp[i] = dp[i - 1];
    ant[i] = 0;
    if(bst[i] != 0){
      if(dp[i] < dp[bst[i] - 1] + 4){
        dp[i] = dp[bst[i] - 1] + 4;
        ant[i] = 1;
      }
    }
    if(bst2[i] != 0){
      if(dp[i] < dp[bst2[i] - 1] + 4){
        dp[i] = dp[bst2[i] - 1] + 4;
        ant[i] = 2;
      }
      
    }
  }

  printf("%d\n",dp[n]);
  int nod = n;
  vector<int> elems;

  while(nod){
    if(ant[nod] == 0){
      nod--;
    }else if(ant[nod] == 1){
      elems.push_back(a[nod]);
      elems.push_back(a[bst[nod]]);
      elems.push_back(a[nod]);
      elems.push_back(a[bst[nod]]);
      nod = bst[nod] - 1;
    }else{
      elems.push_back(a[nod]);
      elems.push_back(a[bst2[nod]]);
      elems.push_back(a[nod]);
      elems.push_back(a[bst2[nod]]);
      nod = bst2[nod] - 1;
    }
  }

  reverse(elems.begin(),elems.end());

  for(auto it:elems){
    printf("%d ",it);
  }

  return 0;
}
