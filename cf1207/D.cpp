#include <bits/stdc++.h>

using namespace std;

const int MOD = 998244353;

int n;
vector<int> a,b;
vector<pair<int,int> > v;
int fa[int(3e5) + 5];

int fact(int x){
    if(x <= 1){
        return 1;
    }
    if(fa[x] == 0){
        fa[x] = 1LL * x * fact(x - 1) % MOD;
    }
    return fa[x];
}

int main() {

    scanf("%d",&n);

    for(int i = 1;i <= n;i++){
        int x,y;
        scanf("%d %d",&x,&y);
        a.push_back(x);
        b.push_back(y);
        v.push_back({x,y});
    }

    a.push_back(-1);
    b.push_back(-1);
    v.push_back({-1,-1});
    sort(a.begin(),a.end());
    sort(b.begin(),b.end());
    sort(v.begin(),v.end());
    
    int ans = fact(n);

    int cnt = 1;
    int tmp = 1;
    for(int i = 2;i <= n;i++){
        if(a[i] == a[i - 1]){
            cnt++;
        }
        if(a[i] != a[i - 1]){
            tmp = 1LL * tmp * fact(cnt) % MOD;
            cnt = 1;
        }
    }
    tmp = 1LL * tmp * fact(cnt) % MOD;
    ans = (MOD + ans - tmp) % MOD;

    cnt = 1;
    tmp = 1;
    for(int i = 2;i <= n;i++){
        if(b[i] == b[i - 1]){
            cnt++;
        }
        if(b[i] != b[i - 1]){
            tmp = 1LL * tmp * fact(cnt) % MOD;
            cnt = 1;
        }
    }
    tmp = 1LL * tmp * fact(cnt) % MOD;
    ans = (MOD + ans - tmp) % MOD;
    
    bool ok = true;

    for(int i = 2;i <= n;i++){
        ok &= (v[i - 1].second <= v[i].second);
    }

    if(ok){
        cnt = 1;
        tmp = 1;
        for(int i = 2;i <= n;i++){
            if(v[i] == v[i - 1]){
                cnt++;
            }
            if(v[i] != v[i - 1]){
                tmp = 1LL * tmp * fact(cnt) % MOD;
                cnt = 1;
            }
        }
        tmp = 1LL * tmp * fact(cnt) % MOD;
        ans = (ans + tmp) % MOD;
    }

    printf("%d\n",ans);

    return 0;
}
