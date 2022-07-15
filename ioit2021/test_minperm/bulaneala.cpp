#include <bits/stdc++.h>

using namespace std;

int gcd(int a,int b){
  if(!b){
    return a;
  }
  return gcd(b, a % b);
}

int main(){

  int n, k;

  scanf("%d %d", &n, &k);

  vector<int> perm(n, 0);
  vector<int> lengths(k, 0);

  for(auto &it:perm){
    scanf("%d", &it);
  }
  
  int __gcd = 0;

  for(auto &it:lengths){
    scanf("%d", &it);
    __gcd = gcd(__gcd, it);
  }

  vector<int> values;
  vector<int> ans(n, 0);
  for(int i = 0;i < __gcd;i++){
    values.clear();
    for(int j = i;j < n;j += __gcd){
      values.push_back(perm[j]);
    }
    sort(values.begin(), values.end());
    for(int j = 0;j < (int)values.size();j++){
      ans[j * __gcd + i] = values[j];
    }
  }

  for(auto it:ans){
    printf("%d ",it);
  }
  printf("\n");
  
  return 0;
}
