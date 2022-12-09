#include <bits/stdc++.h>

using namespace std;

const int SIGMA = 2;

struct node_t{
  node_t* sons[SIGMA];
  node_t(){
    memset(sons, 0 ,sizeof(sons));
  }
};

void insert(node_t* root, int element, int position) {
  if(position < 0){
    return ;
  }
  int k = ((element >> position) & 1);
  if(root->sons[k] == NULL){
    root->sons[k] = new node_t();
  }
  insert(root->sons[k], element, position - 1);
}

int get_best(node_t* root, int element, int position){
  if(position < 0){
    return 0;
  }
  int k = ((element >> position) & 1);
  if(root->sons[!k] != NULL){
    return (1 << position) | get_best(root->sons[!k], element, position - 1);
  }
  return get_best(root->sons[k], element, position - 1);
}

int main(){

  int n;
  scanf("%d", &n);

  vector<int> v(n, 0 );

  for(auto &it:v){
    scanf("%d", &it);
  }

  vector<int> tmp;

  vector<int> best(n, 0);

  for(int i = n - 1;i >= 0;i--){
    tmp.push_back(v[i]);
    sort(tmp.begin(), tmp.end());
    reverse(tmp.begin(), tmp.end());
    tmp.resize(min(tmp.size(), (size_t) 2));
    if((int)tmp.size() == 2){
      best[i] = tmp[0] + tmp[1];
    }
  }

  node_t* root = new node_t();

  long long answer = 0;

  for(int i = 0;i < n;i++){
    int best_xor = 0;
    if(i > 0){
      best_xor = get_best(root, v[i], 30);
    }
    if(i + 1 < n){
      answer = max(answer, 1LL * best_xor * best[i + 1]);
    }
    insert(root, v[i], 30);
  }

  printf("%lld\n", answer);

  return 0;
}
