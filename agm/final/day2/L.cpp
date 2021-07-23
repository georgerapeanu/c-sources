#include <bits/stdc++.h>

using namespace std;

const int NMAX = 1e6;

int n;
int v[NMAX + 5];

struct node_t{
  node_t* son[2];
  node_t(){
    memset(son,0,sizeof(son));
  }
};

void ins(node_t* root,int pos,int value){
  if(pos < 0){
    return;
  }
  int b = (value >> pos) & 1;
  if(root->son[b] == NULL){
    root->son[b] = new node_t();
  }
  ins(root->son[b],pos - 1,value);
}

int query(node_t *root,int pos,int value){
  if(pos < 0){
    return 0;
  }
  int b = (value >> pos) & 1;
  if(root->son[!b] != NULL){
    return query(root->son[!b],pos - 1,value) | (1 << pos);
  }
  return query(root->son[b],pos - 1,value);
}

int main(){

  node_t* root = new node_t();

  scanf("%d",&n);

  for(int i = 1;i <= n;i++){
    scanf("%d",&v[i]);
    ins(root,30,v[i]);
  }

  int answer = 0;

  for(int i = 1;i <= n;i++){
    answer = max(answer,query(root,30,v[i]));
  }

  printf("%d\n",answer);

  return 0;
}
