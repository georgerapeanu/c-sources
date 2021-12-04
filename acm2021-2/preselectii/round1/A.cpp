#include <bits/stdc++.h>

using namespace std;

const int NMAX = 1e4;
const long double eps = 1e-6;

int n,l,w;
pair<long double,long double> segm[NMAX + 5];

bool cmp( const pair<long double,long double> &a,
          const pair<long double,long double> &b){
    if(fabs(a.first - b.first) > eps){
      return a.first < b.first;
    }
    return a.second > b.second;
}

bool cover( const pair<long double,long double> &a,
          const pair<long double,long double> &b){
  return (a.first - b.first) < eps && (a.second - b.second) > -eps;
}
int main(){

    while(scanf("%d %d %d",&n,&l,&w) == 3){
      for(int i = 1;i <= n;i++){
        int x,r;
        scanf("%d %d",&x,&r);
        if(2 * r <= w){
          n--;
          i--;
          continue;
        }
        long double d = sqrt((long double)(1LL * r * r - ((long double)w) * w / 4));
        segm[i] = {x - d,x + d};
      }
    


      sort(segm + 1,segm + 1 + n,cmp);
      vector<pair<long double,long double > > newSegm;
  
      for(int i = 1;i <= n;i++){
        if(newSegm.empty() == false && cover(newSegm.back(),segm[i])){
          continue;
        }
        newSegm.push_back(segm[i]);
      }

      if(newSegm.empty()){
        printf("-1\n");
        continue;
      }

      bool ok = true;
      
      ok &= (newSegm[0].first <= eps);
      ok &= (newSegm.back().second >= l - eps);

      for(int i = 0;i < (int)newSegm.size() - 1;i++){
        ok &= (newSegm[i].second - newSegm[i + 1].first >= -eps);
      }

      if(ok == false){
        printf("-1\n");
        continue;
      }
  
      long double last = 0;
      int cnt = 0;
  
      for(int i = 1;i < (int)newSegm.size();i++){
        if(newSegm[i].first - last > eps){
          last = newSegm[i - 1].second;
          cnt++;
        }
      }
      if(last < l + eps){
        cnt++;
      }

      printf("%d\n",cnt);

    }

    return 0;
}
