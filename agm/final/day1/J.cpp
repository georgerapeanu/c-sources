#include <bits/stdc++.h>

using namespace std;

struct node_t{
  node_t* son[2];
  int cnt;

  node_t(){
    memset(son,0,sizeof(son));
    cnt = 0;
  }
};

void insert(node_t *root,int pos,int value){
  root->cnt++;
  if(pos < 0){
    return ;
  }
  int b = (value >> pos) & 1;
  if(root->son[b] == NULL){
    root->son[b] = new node_t();
  }
  insert(root->son[b],pos - 1,value);
}

void remove(node_t *root,int pos,int value){
  root->cnt--;
  if(pos < 0){
    if(root->cnt == 0){
      delete root;
    }
    return ;
  }
  int b = ((value >> pos) & 1);
  remove(root->son[b],pos - 1,value);
}

long long calculate_cost(node_t *root,int pos,int value){
  if(pos < 0){
    return 0;
  }
  long long ans = 0;
  int b = (value >> pos) & 1;
  if(root->son[!b] != NULL){
    ans += (((long long)root->son[!b]->cnt)) * ((1LL << (pos + 2)) - 1);
  }
  if(root->son[b] != NULL){
    ans += calculate_cost(root->son[b],pos - 1,value);
  }
  return ans;
}

int n;
int m;
int q;
map<int,node_t*> root;
long long ans = 0;

void touch(int nod){
  if(root.count(nod) == 0){
    root[nod] = new node_t();
  }
}

int get_cost(int x,int y){
  x ^= y;
  int ans = 1;
  while(x){
    x >>= 1;
    ans <<= 1;
    ans |= 1;
  }
  return ans;
}

int main(){
  scanf("%d",&n);
  scanf("%d",&m);

  while(m--){
    int x,y;
    scanf("%d %d",&x,&y);
    touch(x);
    touch(y);
    insert(root[x],n,y);
    insert(root[y],n,x);
    ans += get_cost(x,y);
  }

  scanf("%d",&q);

  while(q--){
    int t,x,y;
    scanf("%d %d %d",&t,&x,&y);

    touch(x);
    touch(y);

    if(t == 0){
      insert(root[x],n,y);
      insert(root[y],n,x);
      ans += get_cost(x,y);
    }else if(t == 1){
      remove(root[x],n,y);
      remove(root[y],n,x);
      ans -= get_cost(x,y);
    }else{
      printf("%lld\n",ans - calculate_cost(root[x],n,x) - calculate_cost(root[y],n,y) + calculate_cost(root[x],n,y) + calculate_cost(root[y],n,x));
      //printf("%lld\n",ans);
    }
  }

  return 0;
}

