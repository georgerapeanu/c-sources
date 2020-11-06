#include <bits/stdc++.h>

using namespace std;

int n,k;
vector<long long> a;
vector<long long> sz;
vector<pair<long long,long long> > v;
vector<long long> min_start;

long long get_in_range(long long st,long long dr,long long val){
    val -= st;
    val %= (dr - st + 1);
    if(val < 0){
        val += (dr - st + 1);
    }
    val += st;
    return val;
}

int main() {

    scanf("%d %d",&n,&k);

    for(int i = 1;i <= n;i++){
        int l,r,val;
        scanf("%d %d %d",&l,&r,&val);
        if(false && v.size() && v.back().second == l){
            v.back().second = r;
            a.back() += val;
        }
        else{
            v.push_back({l,r});
            a.push_back(val);
        }
    }

    for(int i = 0;i < (int)a.size();i++){
        sz.push_back(v[i].second - v[i].first);
    }

    for(int i = 0;i < (int)a.size();i++){
        min_start.push_back(max(0LL,-(1LL * sz[i] * k - a[i])));
    }

    for(int i = (int)a.size() - 2;i >= 0;i--){
        if(v[i].second == v[i + 1].first){
            min_start[i] = max(0LL,min_start[i + 1] + (a[i] - 1LL * sz[i] * k));
        }
    }

    for(int i = 0;i < (int)a.size();i++){
        if(min_start[i] > k){
            printf("-1");
            return 0;
        }
    }
    
    long long ammo = k;
    long long ans = 0;
    for(int i = 0;i < (int)a.size();i++){
        if(ammo < min_start[i]){
            ans += ammo;
            ammo = k;
        }
        ammo -= a[i];
        ans += a[i];
        ammo = get_in_range(0,k - 1,ammo);
    }
    printf("%lld\n",ans);

    return 0;
}
