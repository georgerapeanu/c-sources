#include <bits/stdc++.h>

using namespace std;

const int SIGMA = 'z' - 'a' + 1;

struct node_t{
  node_t* sons[SIGMA];
  int cnt;
  int leaf_cnt;

  
  node_t(){
    memset(sons, 0 ,sizeof(sons));
    cnt = 0;
    leaf_cnt = 0;
  }
};

void insert(node_t* root, const string& s, int pos){
  root->cnt++;
  if(pos >= (int)s.size()){
    root->leaf_cnt++;
    return ;
  }
  if(root->sons[s[pos] - 'a'] == NULL){
    root->sons[s[pos] - 'a'] = new node_t();
  }
  insert(root->sons[s[pos] - 'a'], s, pos + 1);
}

node_t* get_kth_autocomplete(node_t* node, int k, string &answer){
  if(k < node->leaf_cnt){
    return node;
  }
  k -= node->leaf_cnt;
  for(int i = 0;i < SIGMA;i++){
    if(node->sons[i] != NULL){
      if(k < node->sons[i]->cnt){
        answer += i + 'a';
        return get_kth_autocomplete(node->sons[i], k, answer);
      }
      k -= node->sons[i]->cnt;
    }
  }
  assert(false);
}

node_t* get_nontrivial_autocomplete(node_t* node, int k, string& answer){
  if(node->cnt == node->leaf_cnt){
    return node;
  }
  k %= (node->cnt - node->leaf_cnt);
  for(int i = 0;i < SIGMA;i++){
    if(node->sons[i] != NULL){
      if(k < node->sons[i]->cnt){
        answer += 'a' + i;
        return get_kth_autocomplete(node->sons[i], k, answer);
      }
      k -= node->sons[i]->cnt;
    }
  }
  assert(false);
}

string parse(node_t* node, const string &s){
  int cnt = 0;
  string answer = "";
  for(auto it:s){
    if(it == '#'){
      cnt++;
      continue;
    }
    if(node != NULL && cnt > 0){
      node = get_nontrivial_autocomplete(node, cnt - 1, answer);
    }
    if(node == NULL || node->sons[it - 'a'] == NULL){
      node = NULL; 
    }else{
      node = node->sons[it - 'a']; 
    }
    answer += it;
    cnt = 0;
  }
  if(node != NULL && cnt > 0){
    node = get_nontrivial_autocomplete(node, cnt - 1, answer);
  }
  return answer;
}

int main(){

  int n;
  cin >> n;
  node_t* root = new node_t();
  while(n--){
    string s;
    cin >> s;
    insert(root, s, 0);
  }
  string tmp;
  int q;
  cin >> q;

  while(q--){
    string s;
    cin >> s;
    cout << parse(root, s) << "\n";
  }

  return 0;
}
