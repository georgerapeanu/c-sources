#include <bits/stdc++.h>

using namespace std;

const int NMAX = 5e5;

class LinearMinHull {
public:

    vector<pair<long long,long long> > hull;

    bool bad_back(pair<long long,long long> a) {
        if(hull.empty()) {
            return false;
        }

        if((int)hull.size() == 1) {
            return (hull.back().first == a.first && a.second < hull.back().second);
        }

        pair<long long,long long> p = hull[(int)hull.size() - 2];
        pair<long long,long long> u = hull[(int)hull.size() - 1];

        return (p.second - a.second) * (u.first - p.first) <= (p.second - u.second) * (a.first - p.first);
    }

public:

    void add_line(pair<long long,long long> a) { ///line slopes should be inserted decreasingly
        if(hull.empty()) {
            hull.push_back(a);
            return ;
        }

        if(hull.back().first == a.first && hull.back().second <= a.second) {
            return ;
        }

        while(bad_back(a)) {
            hull.pop_back();
        }

        hull.push_back(a);
    }

    long long query(long long x) {
        int st = 0;
        int dr = (int)hull.size() - 1;

        while(dr - st > 1) {
            int mid = (st + dr) / 2;

            if((hull[mid + 1].second - hull[mid].second) <= (hull[mid].first - hull[mid + 1].first) * x) {
                st = mid;
            }
            else {
                dr = mid;
            }
        }
        return min(hull[st].first * x + hull[st].second,hull[dr].first * x + hull[dr].second);
    }

};

int n;
vector<int> graph[NMAX + 5];
long long ans = 1LL << 60;
long long dp[NMAX + 5];
int weight[NMAX + 5];

void dfs(int nod,int tata) {
    weight[nod] = 1;

    vector<int> sons;
    for(auto it:graph[nod]) {
        if(it == tata) {
            continue;
        }
        sons.push_back(it);
        dfs(it,nod);
        weight[nod] += weight[it];
    }

    dp[nod] = 1LL * weight[nod] * weight[nod];

    for(auto it:sons) {
        dp[nod] = min(dp[nod],dp[it] + 1LL * (weight[nod] - weight[it]) * (weight[nod] - weight[it]));
        ans = min(ans,dp[it] + 1LL * (n - weight[it]) * (n - weight[it]));
    }

    sort(sons.begin(),sons.end(),[&](int a,int b) {
        return weight[a] > weight[b];
    });

    LinearMinHull hull;

    for(auto it:sons) {
        pair<long long,long long> line = {2 * weight[it],1LL * weight[it] * weight[it] + dp[it]};

        if(hull.hull.empty() == false) {
            ans = min(ans,dp[it] + 1LL * (n - weight[it]) * (n - weight[it]) + hull.query(weight[it] - n));
        }

        hull.add_line(line);
    }

    if(tata == 0) {
        ans = min(ans,dp[nod]);
    }
}

int main() {

    scanf("%d",&n);

    for(int i = 1; i < n; i++) {
        int x,y;
        scanf("%d %d",&x,&y);
        graph[x].push_back(y);
        graph[y].push_back(x);
    }

    dfs(1,0);

    printf("%lld\n",1LL * n * (n - 1) / 2 + (1LL * n * n - ans) / 2);

    return 0;
}
