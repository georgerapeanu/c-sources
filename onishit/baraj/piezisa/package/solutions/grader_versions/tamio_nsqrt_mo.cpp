/* tamio, nsqrt cu mo */
#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using cd = complex<double>;

constexpr ll maxn = 2e5 + 10, maxb = sqrt(maxn) + 10;

int n, q, v[maxn] = {};

vector<pair<int, int>> queries, by_bucket[maxb];
map<pair<int, int>, int> sols;
map<int, int> normalizare;

namespace solver {
int ret = 1e9, poz_st = 0, poz_dr = 10, next_left[maxn], next_right[maxn] = {};

vector<pair<int*, int>> updates;
void modify(int& x, int y) {
    updates.emplace_back(&x, x);
    x = y;
}

void init(int n) {
    poz_dr = n;
    for (auto& x : next_right) x = 1e9;
    for (auto& x : next_left) x = -1e9;
}

void add_st() {
    int x = v[poz_st];
    modify(ret, min(ret, next_right[x] - poz_st));
    modify(next_left[x], poz_st);
    modify(poz_st, poz_st + 1);
}

void add_dr() {
    int x = v[poz_dr];
    modify(ret, min(ret, poz_dr - next_left[x]));
    modify(next_right[x], poz_dr);
    modify(poz_dr, poz_dr - 1);
}

void undo_add() {
    for (int i = 0; i < 3; ++i) {
        *updates.back().first = updates.back().second;
        updates.pop_back();
    }
}
}  // namespace solver

void solve(int _n, int _v[], int _q, int _l[], int _r[], int _solutions[]) {
    n = _n;
    q = _q;

    for (int i = 1; i <= n; ++i) v[i] = _v[i - 1];

    for (int i = 1; i <= n; ++i) v[i] ^= v[i - 1];
    for (int i = 0; i <= n; ++i) normalizare[v[i]] = 0;

    {
        int x = 0;
        for (auto& y : normalizare) y.second = x++;
    }

    for (int i = 0; i <= n; ++i) v[i] = normalizare[v[i]];

    queries.resize(q);
    for (int i = 0; i < q; ++i) {
        auto& x = queries[i];
        x.first = _l[i];
        x.second = _r[i];

        ++x.first;
        by_bucket[x.first / maxb].push_back(x);
    }

    solver::init(n);

    for (int b = 0; b * maxb < n; ++b) {
        while (solver::poz_st < b * maxb) solver::add_st();

        sort(begin(by_bucket[b]), end(by_bucket[b]),
             [](pair<int, int> a, pair<int, int> b) { return a.second > b.second; });

        for (auto x : by_bucket[b]) {
            while (x.second < solver::poz_dr) solver::add_dr();

            while (solver::poz_st < x.first) solver::add_st();

            sols[x] = solver::ret;

            while (solver::poz_st > b * maxb) solver::undo_add();
        }
        while (solver::poz_dr < n - 1) solver::undo_add();
    }

    for (int i = 0; i < q; ++i) _solutions[i] = (sols[queries[i]] > n ? -1:sols[queries[i]]);
}
