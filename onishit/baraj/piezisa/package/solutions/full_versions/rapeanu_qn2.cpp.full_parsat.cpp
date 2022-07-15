//rapeanu_qn2.cpp
#include <bits/stdc++.h>
using namespace std;

const int LEN = 3;

void solve(int n, int v[], int q, int l[], int r[], int solutions[]){
  vector<int> prefix_xors(n + 1, 0);

  for(int i = 1;i <= n;i++){
    prefix_xors[i] = v[i - 1] ^ prefix_xors[i - 1];
  }

  for(int h = 0;h < q;h++){
    int ans = 1e9;
    for(int i = l[h] + 1;i;i--){
      for(int j = r[h] + 1;j <= n;j++){
        if(prefix_xors[j] == prefix_xors[i - 1]){
          ans = min(ans, j - i + 1);
        }
      }
    }
    if(ans == 1e9){
      ans = -1;
    }
    solutions[h] = ans;
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
