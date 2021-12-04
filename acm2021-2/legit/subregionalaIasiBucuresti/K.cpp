#include <bits/stdc++.h>

using namespace std;


int main(){

  int t;
  scanf("%d",&t);

  while(t--){
    int n;
    scanf("%d",&n);
    vector<long long> v(n,0);
    for(auto &it:v){
      int len;
      scanf("%d",&len);

      while(len--){
        int tmp;
        scanf("%d",&tmp);
        it += tmp;
      }
    }
    sort(v.begin(),v.end());

    long long sum = 0;

    for(int i = 0;i < n;i++){
      sum += 1LL * (n - i) * v[i];
    }

    printf("%.10Lf\n",((long double)sum) / n);
  }

    return 0;
}
