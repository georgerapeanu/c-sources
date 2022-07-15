#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
template<class T> void check_min(T &a, const T &b){ a = (a < b) ? a : b; }
template<class T> void check_max(T &a, const T &b){ a = (a > b) ? a : b; }
#define all(x) (x).begin(), (x).end()

const int N = 65e3 + 3;

int n;
array<int, 3> p[N];
pair<int, bitset<N>> dp[N];

void merge(pair<int, bitset<N>> &l, const pair<int, bitset<N>> &r){
    if(r.first > l.first){
        l = r;
    }
    else if(l.first == r.first){
        l.second |= r.second;
    }
}

struct Fenwick{
    pair<int, bitset<N>> a[N];

    void update(int i, const pair<int, bitset<N>> &val){
        ++i;
        for(; i < N; i += i & -i)
            merge(a[i], val);
    }

    pair<int, bitset<N>> query(int i){
        pair<int, bitset<N>> res;
        ++i;
        for(; i >= 1; i -= i & -i)
            merge(res, a[i]);
        return res;
    }
} f;


pair<int, int> collectFruits(int _N, std::vector<int> x, std::vector<int> y, std::vector<int> z){
    n = _N;

    p[0] = {0, 0, 0};
    for(int i = 1; i <= n; ++i){
        p[i][0] = x[i - 1];
        p[i][1] = y[i - 1];
        p[i][2] = z[i - 1];
        --p[i][2];
    }
    sort(p, p + 1 + n);

    dp[0].second[0] = true;
    f.update(0, dp[0]);

    for(int i = 1; i <= n; ++i){
        dp[i] = f.query(p[i][1]);
        ++dp[i].first;
        if(p[i][2])
            dp[i].second <<= 1;

        f.update(p[i][1], dp[i]);
    }

    for(int i = 0; i < n; ++i)
        merge(dp[n], dp[i]);

    int sum = dp[n].first;
    int best;
    for(int i = sum / 2; i >= 0; --i){
        if(dp[n].second[i] || dp[n].second[sum - i]){
            best = i;
            break;
        }
    }

    int diff = abs(best - (sum - best));
    return {sum, diff};
}
