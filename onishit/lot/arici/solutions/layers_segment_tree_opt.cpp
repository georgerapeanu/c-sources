#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
template<class T> void check_min(T &a, const T &b){ a = (a < b) ? a : b; }
template<class T> void check_max(T &a, const T &b){ a = (a > b) ? a : b; }
#define all(x) (x).begin(), (x).end()

const int N = 35e3 + 3;

int n, dp[N];
array<int, 3> p[N];
bitset<N> b[N];

vector<int> l[N];

struct SegmentTree{
    bitset<N> st[4 * N];
    int sz;

    void init(int i, int l, int r, const vector<int> &idx){
        if(l == r){
            st[i] = b[idx[l]];
            return;
        }

        int mid = (l + r) >> 1;
        init(2 * i + 1, l, mid, idx);
        init(2 * i + 2, mid + 1, r, idx);
        st[i] = st[2 * i + 1] | st[2 * i + 2];
    }

    void init(int sz, const vector<int> &idx){
        this->sz = sz;
        init(0, 0, sz - 1, idx);
    }

    bitset<N> query(int sl, int sr, int i, int l, int r){
        if(sl <= l && r <= sr)
            return st[i];

        int mid = (l + r) >> 1;

        if(sl <= mid && mid + 1 <= sr)
            return query(sl, sr, 2 * i + 1, l, mid) | query(sl, sr, 2 * i + 2, mid + 1, r);
        if(sr <= mid)
            return query(sl, sr, 2 * i + 1, l, mid);
        return query(sl, sr, 2 * i + 2, mid + 1, r);
    }

    bitset<N> query(int l, int r){
        if(l > r) return bitset<N>();
        return query(l, r, 0, 0, sz - 1);
    }
} st;

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

        //vector<int> lf = l[i - 1];
        vector<int> lf;
        lf.push_back(0);
        for(int j = 1; j < l[i - 1].size(); ++j){
            if(b[l[i - 1][j]] != b[l[i - 1][j - 1]]){
                lf.push_back(j);
            }
        }

        vector<pair<int, int>> new_range;

        ptr_l = 0, ptr_r = -1;
        for(auto [lp, rp]: range){
            while(ptr_l + 1 < lf.size() && lf[ptr_l + 1] <= lp)
                ++ptr_l;
            while(ptr_r + 1 < lf.size() && lf[ptr_r + 1] <= rp)
                ++ptr_r;
            new_range.push_back({ptr_l, ptr_r});
        }

        range = new_range;
        for(int &x: lf)
            x = l[i - 1][x];

        st.init(lf.size(), lf);
        for(int j = 0; j < l[i].size(); ++j){
            auto [le, re] = range[j];
            b[l[i][j]] = st.query(le, re);
            b[l[i][j]] <<= p[l[i][j]][2];
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