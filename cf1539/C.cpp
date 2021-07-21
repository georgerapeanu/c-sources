#include <bits/stdc++.h>

using namespace std;

int n;
long long k,x;

int main(){

    scanf("%d %lld %lld",&n,&k,&x);

    vector<long long> v(n,0);
    for(auto &it:v){
      scanf("%lld",&it);
    }

    sort(v.begin(),v.end());

    vector<long long> stuff;

    for(int i = 0;i + 1 < (int)v.size();i++){
      stuff.push_back(max(0LL,v[i + 1] - v[i] - 1) / x);
    }

    sort(stuff.begin(),stuff.end());

    int ans = n;

    for(auto it:stuff){
      if(it <= k){
        ans --;
        k -= it;
      }
    }

    printf("%d\n",ans);

    return 0;
}
