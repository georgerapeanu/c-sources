#include <bits/stdc++.h>

using namespace std;

const long long inf = 1e18;

long long add(long long a,long long b){
  if(a >= inf - b){
    return inf;
  }
  return a + b;
}

int main(){
  int n;
  long long k;

  scanf("%d %lld",&n,&k);

  vector<long long> len(n + 1,0);
  len[1] = len[2] = 1;

  for(int i = 3;i <= n;i++){
    len[i] = add(len[i - 2],len[i - 1]);
  }

  while(n > 2){
    if(len[n - 2] >= k){
      n -= 2;
    }else{
      k -= len[n - 2];
      n--;
    }
  }

  printf(n == 1 ? "N":"A");

  return 0;
}
