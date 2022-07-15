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

    for(int i = 0; i <= n; ++i)
        l[dp[i]].push_back(i);

    int sum = 0;
    for(int i = 0; i <= n; ++i)
        check_max(sum, dp[i]);

    b[0][0] = true;

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

        vector<int> v(n + 1, 0);
        ptr_l = 0, ptr_r = -1;
        for(int j = 0; j < l[i].size(); ++j){
            while(ptr_r < range[j].second){
                ++ptr_r;
                for(int k = 0; k <= n; ++k)
                    v[k] += b[l[i - 1][ptr_r]][k];
            }
            while(ptr_l < range[j].first){
                for(int k = 0; k <= n; ++k)
                    v[k] -= b[l[i - 1][ptr_l]][k];
                ++ptr_l;
            }

            if(!p[l[i][j]][2]){
                for(int k = 0; k <= n; ++k)
                    b[l[i][j]][k] = (bool)v[k];
            }
            else{
                for(int k = 0; k <= n - 1; ++k)
                    b[l[i][j]][k + 1] = (bool)v[k];
            }
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