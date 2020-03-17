#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

FILE *f = fopen("flooow.in","r");
FILE *g = fopen("flooow.out","w");

int n,k;
vector<int> v;
vector<pair<long long,int> > dp;

pair<long long,int> check(int penal) {
    long long pref = 0;
    pair<long long,int> bst = {0,0};
    for(int i = 1; i < (int)v.size(); i++) {
        pref += v[i];
        pair<long long,int> tmp = make_pair(bst.first + pref - penal,bst.second + 1);
        dp[i] = max(dp[i - 1],tmp);
        tmp = make_pair(dp[i].first - pref,dp[i].second);
        bst = max(bst,tmp);
    }

    return dp.back();
}

long long solve() {
    dp.resize(v.size());

    int l = -1,r = 1e5;

    while(r - l > 1) {
        int mid = (l + r) / 2;
        if(check(mid).second <= k) {
            r = mid;
        }
        else {
            l = mid;
        }
    }

    pair<long long,int> tmp = check(r);

    return tmp.first + 1LL * r * tmp.second + max(0LL,1LL * (k - tmp.second) * l);
}

int main() {

    fscanf(f,"%d %d",&n,&k);

    long long ans = 0;

    for(int i = 1; i <= n; i++) {
        int k;
        fscanf(f,"%d",&k);
        v.resize(k + 1);
        for(int j = 1; j <= k; j++) {
            fscanf(f,"%d",&v[j]);
        }
        ans += solve();
    }

    fprintf(g,"%d %lld\n",k,ans);

    fclose(f);
    fclose(g);

    return 0;
}
