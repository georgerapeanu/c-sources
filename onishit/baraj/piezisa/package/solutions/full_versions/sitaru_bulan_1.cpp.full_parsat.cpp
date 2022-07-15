//sitaru_bulan_1.cpp
#include <bits/stdc++.h>

using namespace std;

const int BLN = 100;

void solve(int N, int v[], int Q, int lft[], int rgt[], int solutions[]) {
    for(int i = 1; i < N; i++)  v[i] ^= v[i - 1];

    int K;
    unordered_map<int, int> nrm;
    K = 1;
    nrm[0] = 0;
    for(int i = 0; i < N; i++) {
        if (!nrm.count(v[i])) {
            nrm[v[i]] = K++;
        }
        v[i] = nrm[ v[i] ];
    }

    vector<int> pos[K];

    pos[0].push_back(-1);
    for(int i = 0; i < N; i++)
        pos[ v[i] ].push_back(i);

    for(int q = 0; q < Q; q++) {
        int l = lft[q], r = rgt[q];

        int ans = N + 1;
        for(int j = l - 1; j >= -1 && j >= l - BLN; j--) {
            int val = j == -1 ? 0 : v[j];
            auto it = lower_bound(pos[val].begin(), pos[val].end(), r);
            if(it != pos[val].end()) {
                ans = min(ans, (*it) - j);
            }
        }

        for(int j = r; j < N && j < r + BLN; j++) {
            int val = v[j];
            auto it = lower_bound(pos[val].begin(), pos[val].end(), l);
            if(it != pos[val].begin()) {
                it--;
                ans = min(ans, j - (*it));
            }
        }
        if(ans == N + 1)    ans = -1;
        solutions[q] = ans;
    }
}
#include <stdio.h>
#include <stdlib.h>

#define LEN (1<<12)
static char buff[LEN];
static int ind = LEN - 1;

static int int32(){
  int ans = 0;

  while(buff[ind] < '0' || buff[ind] > '9'){
    if(++ind >= LEN){
      fread(buff, 1, LEN, stdin);
      ind = 0;
    }
  }
  
  while(!(buff[ind] < '0' || buff[ind] > '9')){
    ans = ans * 10 + buff[ind] - '0';
    if(++ind >= LEN){
      fread(buff, 1, LEN, stdin);
      ind = 0;
    }
  }
  return ans;
}

int main(){
  
  int n, q;
  n = int32();
  int* v = (int*)malloc(sizeof(int) * n);

  for(int i = 0;i < n;i++){
    v[i] = int32();
  }

  q = int32();

  int* l = (int*)malloc(sizeof(int) * q);
  int* r = (int*)malloc(sizeof(int) * q);
  for(int i = 0;i < q;i++){
    l[i] = int32();
    r[i] = int32();
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
