#include <bits/stdc++.h>

using namespace std;

inline void Boost() {
    ios::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);
}
typedef long long int ll;
typedef long double ld;

const int NMax = 5e5 + 50;

int BIT[NMax];

void update(int pos, int n) {
    while (pos <= n) {
        ++BIT[pos];
        pos += pos & (-pos);
    }
}
int querryBIT(int pos) {
    int ret = 0;
    while (pos) {
        ret += BIT[pos];
        pos -= pos & (-pos);
    }
    return ret;
}

int findKth(int pos, int m) {
    int lo = 1;
    int hi = m;
    int best = 1;

    while (lo <= hi) {
        int mid = (lo + hi) / 2;
        int val = querryBIT(mid);

        if (val < pos) {
            lo = mid + 1;
        } else {
            best = mid;
            hi = mid - 1;
        }
    }
    return best;
}

int main() {
    Boost();

    int n, m, q;
    cin >> n >> m >> q;

    vector < pair < int, ll > > v(m + 5);
    for (int i = 0; i < (int)v.size(); ++i) {
        v[i].first = i;
    }

    for (int i = 0; i < n; ++i) {
        int x;
        cin >> x;
        ++v[x].second;
    }

    sort(v.begin() + 1, v.begin() + m + 1, [&](const pair < int, int > &a, const pair < int, int > &b) {
        if (a.second != b.second) return a.second < b.second;
        return a.first < b.first;
    });

    vector < pair < int, ll > > Q(q);
    for (int i = 0; i < q; ++i) {
        ll x;
        cin >> x;
        Q[i] = {i, x - n};
    }

    sort(Q.begin(), Q.end(), [&](const pair < int, ll > &a, const pair < int, ll > &b) {
        return a.second < b.second;
    });

    v[m + 1].second = v[m + 2].second = (LLONG_MAX);

    ll nr = 0;
    ll mx = v[1].second;
    ll sofar = 0;
    ll toBring = 0;
    while (nr < m && v[nr + 1].second == mx) {
        ++nr;
        sofar += mx;
        update(v[nr].first, m);
    }

    vector < int > ans(q, 0);
    for (int querry = 0; querry < q; ++querry) {
        ll newMx = 0;
        ll toDo = Q[querry].second;

        // only nr elements
        ll interest = 0;
        if (nr == m) {
            interest = LLONG_MAX;
        } else {
            interest = nr * v[nr + 1].second - sofar;
        }
        // cout << toDo << " " << interest << " ---- ";
        while (toDo > interest) {
            toBring += nr * (v[nr + 1].second - v[nr].second);
            mx = v[nr + 1].second;
            while (nr < m && v[nr + 1].second == mx) {
                ++nr;
                sofar += mx;
                update(v[nr].first, m);
            }

            if (nr == m) {
                interest = LLONG_MAX;
            } else {
                interest = nr * v[nr + 1].second - sofar;
            }
        }

        toDo = toDo - toBring - 1;
        int pos = (toDo % nr) + 1;
        // cout << nr << " " << querry << " " << toDo << " " << pos << endl;
        ans[Q[querry].first] = findKth(pos, m);
    }

    for (auto x : ans) cout << x << "\n";
    return 0;
}
