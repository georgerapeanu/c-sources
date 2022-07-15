#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
template<class T> void check_min(T &a, const T &b){ a = (a < b) ? a : b; }
template<class T> void check_max(T &a, const T &b){ a = (a > b) ? a : b; }
#define all(x) (x).begin(), (x).end()

const int N = 65e3 + 3;

int n, dp[N];
array<int, 3> p[N];
bitset<N> b[N];

vector<int> l[N];

struct Fenwick{
    int a[N];

    void update(int i, int val){
        ++i;
        for(; i < N; i += i & -i)
            check_max(a[i], val);
    }

    int query(int i){
        ++i;
        int res = 0;
        for(; i >= 1; i -= i & -i)
            check_max(res, a[i]);
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

    for(int i = 1; i <= n; ++i){
        dp[i] = f.query(p[i][1]) + 1;
        f.update(p[i][1], dp[i]); 
    }

    for(int i = 0; i <= n; ++i)
        l[dp[i]].push_back(i);

    int sum = 0;
    for(int i = 0; i <= n; ++i)
        check_max(sum, dp[i]);

    b[0][0] = true;

    static bitset<N> g[N];
    for(int i = 1; i <= sum; ++i){
        vector<pair<int, int>> range;
        int ptr_l = 0, ptr_r = -1;
        for(int j = 0; j < l[i].size(); ++j){
            while(ptr_r + 1 < l[i - 1].size() && p[l[i - 1][ptr_r + 1]][0] <= p[l[i][j]][0])
                ++ptr_r;
            while(ptr_l < l[i - 1].size() && p[l[i - 1][ptr_l]][1] > p[l[i][j]][1])
                ++ptr_l;
            range.push_back({ptr_l, ptr_r});
        }

        // 1 - the range for each point of the current layer
        // 2 - the possible splits
        function<void(int, int, int, int)> dnc = [&](int l1, int r1, int l2, int r2) -> void{
            if(l1 > r1)
                return;

            int mid = (l2 + r2) / 2;

            int l3;
            for(l3 = l1; l3 <= r1; ++l3)
                if(range[l3].second >= mid)
                    break;

            int r3;
            for(r3 = r1; r3 >= l1; --r3)
                if(range[r3].first <= mid)
                    break;

            dnc(l1, l3 - 1, l2, mid - 1);
            dnc(r3 + 1, r1, mid + 1, r2);

            if(l3 > r3)
                return;

            if(mid >= range[l3].first){
                g[mid] = b[l[i - 1][mid]];
            }
            for(int j = mid - 1; j >= range[l3].first; --j)
                g[j] = g[j + 1] | b[l[i - 1][j]];

            if(mid + 1 <= range[r3].second){
                g[mid + 1] = b[l[i - 1][mid + 1]];
            }
            for(int j = mid + 2; j <= range[r3].second; ++j)
                g[j] = g[j - 1] | b[l[i - 1][j]];

            for(int j = l3; j <= r3; ++j){
                if(range[j].second > mid)
                    b[l[i][j]] = g[range[j].first] | g[range[j].second];
                else
                    b[l[i][j]] = g[range[j].first];
            }
        };

        dnc(0, (int)l[i].size() - 1, 0, (int)l[i - 1].size() - 1);

        for(int j = 0; j < l[i].size(); ++j)
            if(p[l[i][j]][2])
                b[l[i][j]] <<= 1;
    }

    for(int i = 1; i < l[sum].size(); ++i)
        b[l[sum][0]] |= b[l[sum][i]];

    auto poss = b[l[sum][0]];
    int best;
    for(int i = sum / 2; i >= 0; --i){
        if(poss[i] || poss[sum - i]){
            best = i;
            break;
        }
    }

    int diff = abs(best - (sum - best));
    return {sum, diff};
}
