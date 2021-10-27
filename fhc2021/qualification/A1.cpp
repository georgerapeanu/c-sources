#include <bits/stdc++.h>

using namespace std;

const int SIGMA = 'Z' - 'A' + 1;
vector<int> trans_graph[SIGMA + 5]; /// LGBTQ+
int dist[SIGMA + 5];
int weight[SIGMA + 5];

void bfs(int root){
  for(int i = 1;i <= SIGMA;i++){
    dist[i] = 0;
  }

  queue<int> q;
  
  dist[root] = 1;
  q.push(root);

  while(q.empty() == false){
    int nod = q.front();
    q.pop();
    for(auto it:trans_graph[nod]){
      if(dist[it] == 0){
        dist[it] = 1 + dist[nod];
        q.push(it);
      }
    }
  }
}

bool is_vowel[SIGMA + 5];

int main(){
  
  is_vowel['A' - 'A' + 1] = true;
  is_vowel['E' - 'A' + 1] = true;
  is_vowel['I' - 'A' + 1] = true;
  is_vowel['O' - 'A' + 1] = true;
  is_vowel['U' - 'A' + 1] = true;

  int t;
  cin >> t;

  for(int h = 1;h <= t;h++){
    for(int i = 1;i <= SIGMA;i++){
      dist[i] = 0;
      weight[i] = 0;
      trans_graph[i].clear();
    }
    int m;
    string s;

    cin >> s;

    for(auto &it:s){
      weight[it - 'A' + 1]++;
    }

    for(int i = 1;i <= SIGMA;i++){
      for(int j = 1;j <= SIGMA;j++){
        if(is_vowel[i] != is_vowel[j]){
          trans_graph[j].push_back(i);
        }
      }
    }

    int ans = 1e9;
    for(int i = 1;i <= SIGMA;i++){
      bfs(i);
      int local_ans = 0;
      for(int i = 1;i <= SIGMA;i++){
        local_ans += (dist[i] - 1) * weight[i];
        if(weight[i] > 0 && dist[i] == 0){
          local_ans = 1e9;
        }
      }
      ans = min(ans,local_ans);
    }

    printf("Case #%d: %d\n",h,(ans == 1e9 ? -1:ans));
  }

  return 0;
}
