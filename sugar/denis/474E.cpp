#include <cstdio>
#include <vector>
#include <algorithm>
#include <map>

using namespace std;

const int NMAX = 1e5;

int n,d;
long long v[NMAX + 5];
pair<int,int> dp[NMAX + 5];

pair<int,int> pref_aib[NMAX + 5];
pair<int,int> suff_aib[NMAX + 5];

void pref_update(int pos,pair<int,int> val) {
    for(; pos <= NMAX; pos += (-pos) & pos) {
        pref_aib[pos] = max(pref_aib[pos],val);
    }
}

pair<int,int> pref_query(int pos) {
    pair<int,int> ans = {-1,0};
    for(; pos; pos -= (-pos) & pos) {
        ans = max(ans,pref_aib[pos]);
    }
    ans.first++;
    return ans;
}

void suff_update(int pos,pair<int,int> val) {
    for(; pos; pos -= (-pos) & pos) {
        suff_aib[pos] = max(suff_aib[pos],val);
    }
}

pair<int,int> suff_query(int pos) {
    pair<int,int> ans = {-1,0};

    for(; pos <= NMAX; pos += (-pos) & pos) {
        ans = max(ans,suff_aib[pos]);
    }
    ans.first++;
    return ans;
}

int main() {

    vector<long long> norm;

    scanf("%d %d",&n,&d);

    for(int i = 1; i <= n; i++) {
        scanf("%lld",&v[i]);
        norm.push_back(v[i]);
    }

    sort(norm.begin(),norm.end());
    norm.resize(unique(norm.begin(),norm.end()) - norm.begin());
    vector<int> st(norm.size(),-1);
    vector<int> dr(norm.size(),(int)norm.size());

    for(int i = 0; i < (int)norm.size(); i++) {
        if(i > 0) {
            st[i] = st[i - 1];
        }
        while(st[i] < i && norm[i] - norm[st[i] + 1] >= d) {
            st[i]++;
        }
    }

    for(int i = (int)norm.size() - 1; i >= 0; i--) {
        if(i < (int)norm.size() - 1) {
            dr[i] = dr[i + 1];
        }
        while(dr[i] > i && norm[dr[i] - 1] - norm[i] >= d) {
            dr[i]--;
        }
    }

    map<long long,int> to_norm;

    for(int i = 0; i < (int)norm.size(); i++) {
        to_norm[norm[i]] = i;
    }

    int id = n;

    for(int i = n; i; i--) {
        int norm_id = to_norm[v[i]];
        dp[i] = max(pref_query(st[norm_id] + 1),suff_query(dr[norm_id] + 1));
        pref_update(norm_id + 1, {dp[i].first,i});
        suff_update(norm_id + 1, {dp[i].first,i});
        if(dp[id] < dp[i]) {
            id = i;
        }
    }

    printf("%d\n",dp[id].first);

    while(id) {
        printf("%d ",id);
        id = dp[id].second;
    }

    return 0;
}
