#include <bits/stdc++.h>

using namespace std;

const int NMAX = 2e5;
const long double PI = acos(-1);

int n;
int h;
pair<int,int> p[NMAX + 5];

long long det(pair<int,int> a,pair<int,int> b,pair<int,int> c){
  return 1LL * a.first * (b.second - c.second) + 1LL * b.first * (c.second - a.second) + 1LL * c.first * (a.second - b.second);
}

int main(){

  scanf("%d %d",&n,&h);

  for(int i = 1;i <= n;i++){
    scanf("%d %d",&p[i].first,&p[i].second);
  }

  pair<int,int> tower = p[n];
  tower.second += h;
  long double ans = 0;
  pair<int,int> last_point = p[n];

  for(int i = n;i > 1;i--){
    long long d = (det(tower,last_point,p[i - 1]));
    if(d <= 0){
      if(d == 0 && det(tower,p[i - 1],p[i]) == 0){
        long double x = p[i].first;
        long double y = p[i].second;
        ans += sqrt((p[i - 1].first - x) * (p[i - 1].first - x) + (p[i - 1].second - y) * (p[i - 1].second - y));
        continue;
      }
      
      int a = last_point.second - (tower.second);
      int b = -last_point.first + (tower.first);
      long long c = -1LL * a * tower.first - 1LL * b * (tower.second);

      int ap = p[i].second - p[i - 1].second;
      int bp = p[i - 1].first - p[i].first;
      long long cp = -1LL * ap * p[i].first - 1LL * bp * p[i].second;

      long double y = (1LL * a * cp - 1LL * ap * c) / ((long double)(1LL * ap * b - 1LL * a * bp));
      long double x = (1LL * b * cp - 1LL * bp * c) / ((long double)(1LL * bp * a - 1LL * b * ap));
      last_point = p[i - 1];

      if(x < min(p[i - 1].first,p[i].first) || x > max(p[i].first,p[i - 1].first)){
        continue;
      }
      
      if(y < min(p[i - 1].second,p[i].second) || y > max(p[i].second,p[i - 1].second)){
        continue;
      }
      
      ans += sqrt((p[i - 1].first - x) * (p[i - 1].first - x) + (p[i - 1].second - y) * (p[i - 1].second - y));
    }
  }

  printf("%.10Lf\n",ans);

  return 0;
}
