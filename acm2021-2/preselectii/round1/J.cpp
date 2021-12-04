#include <bits/stdc++.h>

using namespace std;

const int NMAX = 1e5;

int n;
pair<int,int> p[NMAX + 5];

int main(){

    vector<pair<int,int>> v1,v2;

    scanf("%d",&n);

    for(int i = 1;i <= n;i++){
      scanf("%d %d",&p[i].first,&p[i].second);
    }

    for(int i = 1;i <= n;i++){
      v1.push_back({p[(i % n) + 1].first - p[i].first,p[(i % n) + 1].second - p[i].second});
      v2.push_back({-p[(i % n) + 1].first + p[i].first,-p[(i % n) + 1].second + p[i].second});
    }

    sort(v1.begin(),v1.end());
    sort(v2.begin(),v2.end());

    bool ok = true;

    for(int i = 0;i < n;i++){
      ok &= (v1[i] == v2[i]);
    }

    printf(ok ? "yes":"no");
    
    return 0;
}
