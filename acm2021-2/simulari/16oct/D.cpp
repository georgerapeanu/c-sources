#include <bits/stdc++.h>

using namespace std;

int gcd(int a,int b){
  if(b == 0){
    return (a < 0 ? -a:a);
  }
  return gcd(b,a % b);
}

int main(){
  int t;
  int n;
    
  scanf("%d",&t);

  while(t--){
    scanf("%d",&n);
    vector<pair<int,int> > v(n);

    map<pair<int,int>,int > stuff;
    long long ans = 0;
    for(auto &it:v){
      int x,y,u,v;
      scanf("%d %d %d %d",&x,&y,&u,&v);
      it = make_pair(u - x,v - y);

      int _g = gcd(it.first,it.second);

      it.first /= _g;
      it.second /= _g;
      stuff[it]++;
      ans += stuff[make_pair(-it.first,-it.second)];
    }
    printf("%lld\n",ans);
  }

  return 0;
}
