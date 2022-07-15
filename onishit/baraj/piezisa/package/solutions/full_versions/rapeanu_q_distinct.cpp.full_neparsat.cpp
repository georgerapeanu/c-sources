//rapeanu_q_distinct.cpp
#include<bits/stdc++.h>

using namespace std;

void solve(int n, int v[], int q, int l[], int r[], int solutions[]){

  vector<int> prefix_xors(n + 1, 0);
  vector<int> values = {0};

  for(int i = 1;i <= n;i++){
    prefix_xors[i] = prefix_xors[i - 1] ^ v[i - 1];
    values.push_back(prefix_xors[i]);
  }

  for(int i = 0;i < q;i++){
    solutions[i] = 1e9;
  }
  
  sort(values.begin(), values.end());
  values.resize(unique(values.begin(), values.end()) - values.begin());

  vector<int> nxt(n + 1, -1);
  vector<int> ant(n + 1, -1);
  
  for(auto it:values){
    for(int i = 0;i <= n;i++){
      ant[i] = (prefix_xors[i] == it ? i:(i == 0 ? -1:ant[i - 1]));
    }
    for(int i = n;i >= 0;i--){
      nxt[i] = (prefix_xors[i] == it ? i:(i == n ? -1:nxt[i + 1]));
    }

    for(int i = 0;i < q;i++){
      if(ant[l[i]] != -1 && nxt[r[i] + 1] != -1){
        solutions[i] = min(solutions[i], nxt[r[i] + 1] - ant[l[i]]);
      }
    }
  }

  for(int i = 0;i < q;i++){
    if(solutions[i] == 1e9){
      solutions[i] = -1;
    }
  }
}
#include <stdio.h>
#include <stdlib.h>

int main(){
  
  int n, q;
  scanf("%d", &n);
  int* v = (int*)malloc(sizeof(int) * n);

  for(int i = 0;i < n;i++){
    scanf("%d", &v[i]);
  }

  scanf("%d", &q);

  int* l = (int*)malloc(sizeof(int) * q);
  int* r = (int*)malloc(sizeof(int) * q);
  for(int i = 0;i < q;i++){
    scanf("%d %d", &l[i], &r[i]);
  }

  int* answers = (int*)malloc(sizeof(int) * q);

  solve(n, v, q, l, r, answers);

  for(int i = 0;i < q;i++){
    printf("%d\n", answers[i]);
  }

  free(answers);
  free(l);
  free(r);
  free(v);

  return 0;
}
