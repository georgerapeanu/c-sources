#include <bits/stdc++.h>

using namespace std;

int t;
int n;
vector<int> v;

int gcd(int a,int b){
  if(!b) return a;
  return gcd(b,a % b);
}

int main(){

  scanf("%d",&t);

  while(t--){
    scanf("%d",&n);

    v = vector<int>(n,0);

    for(auto &it:v){
      scanf("%d",&it);
    }

    sort(v.begin(),v.end(),[&](int a,int b){return (a & 1) < (b & 1);});

    int ans = 0;

    for(int i = 0;i < n;i++){
      for(int j = i + 1;j < n;j++){
        ans += (gcd(v[i],2 * v[j]) > 1);
      }
    }

    printf("%d\n",ans);
  }

  return 0;
}
