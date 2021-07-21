#include <bits/stdc++.h>

using namespace std;

const int NMAX = 1e5;

int n;
pair<long long,long long> v[NMAX + 5];

int main(){

    scanf("%d",&n);

    long long sum = 0;

    for(int i = 1;i <= n;i++){
      scanf("%lld %lld",&v[i].second,&v[i].first);
      sum += v[i].second;
    }

    sort(v + 1,v + 1 + n);
    reverse(v + 1,v + 1 + n);

    long long last = sum;

    for(auto it:v){
      last -= min(max(0LL,last - it.first),it.second);
    }

    printf("%lld\n",last + sum);



    return 0;
}
