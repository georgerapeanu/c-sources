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

int main(){
    ios::sync_with_stdio(false);
    cin.tie(NULL);

    cin >> n;
    p[0] = {0, 0, 0};
    for(int i = 1; i <= n; ++i){
        cin >> p[i][0] >> p[i][1] >> p[i][2];
        --p[i][2];
    }
    sort(p, p + 1 + n);

    for(int i = 1; i <= n; ++i){
        dp[i] = f.query(p[i][1]) + 1;
        f.update(p[i][1], dp[i]); 
    }

    vector<int> perm(n + 1);
    iota(all(perm), 0);

    sort(all(perm), [&](int l, int r){
        if(dp[l] == dp[r])
            return l < r;
        return dp[l] < dp[r];
    });

    vector<int> pos(n + 1);
    for(int i = 0; i <= n; ++i)
        pos[perm[i]] = i;

    for(int i = 0; i <= n; ++i)
        l[dp[i]].push_back(pos[i]);

    vector<array<int, 3>> p_cp;
    for(int i = 0; i <= n; ++i)
        p_cp.push_back(p[i]);

    for(int i = 0; i <= n; ++i)
        p[i] = p_cp[perm[i]];

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

        int j = 0;
        while(j < l[i].size()){
            int nxt = j;
            for(; nxt < l[i].size(); ++nxt){
                if(range[nxt].first > range[j].second){
                    break;
                }
            }
            --nxt;

            int mid = range[j].second;
            g[mid] = b[l[i - 1][mid]];
            for(int k = mid - 1; k >= range[j].first; --k){
                g[k] = b[l[i - 1][k]];
                g[k] |= g[k + 1];
            }

            if(range[nxt].second > mid){
                g[mid + 1] = b[l[i - 1][mid + 1]];
                for(int k = mid + 2; k <= range[nxt].second; ++k){
                    g[k] = b[l[i - 1][k]];
                    g[k] |= g[k - 1];
                }
            }

            for(int k = j; k <= nxt; ++k){
                if(range[k].second == range[j].second){
                    b[l[i][k]] = g[range[k].first];
                    if(p[l[i][k]][2]){
                        b[l[i][k]] <<= p[l[i][k]][2];
                    }
                    
                }
                else{
                    b[l[i][k]] = g[range[k].first];
                    b[l[i][k]] |= g[range[k].second];
                    if(p[l[i][k]][2]){
                        b[l[i][k]] <<= p[l[i][k]][2];
                    }
                }
            }

            j = nxt + 1;
        }
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
    cout << sum << " " << diff << "\n";
}