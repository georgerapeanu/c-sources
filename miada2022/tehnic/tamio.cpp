#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using cd = complex<double>;

constexpr ll mod = 1e9 + 7, maxn = 2e5 + 10;

static int normalize(int x) {
    if (x >= mod) x -= mod;
    if(x < 0) x += mod;
    return x;
}

struct elem {
    int up, mid, down;
};

elem operator+(const elem& a, const elem& b) {
    return elem{normalize(a.up + b.up), normalize(a.mid + b.mid), normalize(a.down + b.down)};
}

elem operator-(const elem& a, const elem& b) {
    return elem{normalize(a.up - b.up), normalize(a.mid - b.mid), normalize(a.down - b.down)};
}

vector<int> fii[maxn] = {};

int n, tt[maxn] = {}, adanc[maxn] = {}, sz[maxn], rmq[20][2 * maxn] = {}, euler[2 * maxn] = {}, first_ap[maxn] = {},
       last_ap[maxn] = {}, curr_time = 1;

elem curr_value[maxn] = {}, subtree_aib[2 * maxn] = {}, chain_aib[2 * maxn] = {};

template <elem* buf>
void add_aib(int poz, elem x) {
    for (; poz < 2 * maxn; poz += poz & -poz) buf[poz] = (buf[poz] + x);
}

template <elem* buf>
elem query_aib(int poz) {
    elem ret = {};
    for (; poz; poz -= poz & -poz) ret = ret + buf[poz];
    return ret;
}

void build_rmq() {
    for (int i = 1; i < curr_time; ++i) rmq[0][i] = i;

    auto cmp = [](int x, int y) { return adanc[euler[x]] < adanc[euler[y]]; };

    for (int niv = 1; niv < 20; ++niv)
        for (int i = 1, j = 1 + (1 << (niv - 1)); j < curr_time; ++i, ++j)
            rmq[niv][i] = min(rmq[niv - 1][i], rmq[niv - 1][j], cmp);
}

int query_rmq(int i, int j) {
    if(j == i){
      return j;
    }

    auto cmp = [](int x, int y) { return adanc[euler[x]] < adanc[euler[y]]; };
    int niv = log2(j - i);
    return min(rmq[niv][i], rmq[niv][j - (1 << niv)], cmp);
}

int lca(int i, int j) {
    auto t = minmax(first_ap[i], first_ap[j]);
    return euler[query_rmq(t.first, t.second)];
}

elem chain_sum(int i, int j) {
    int l = lca(i, j);
    auto t = query_aib<chain_aib>(first_ap[l]);
    return query_aib<chain_aib>(first_ap[i]) + query_aib<chain_aib>(first_ap[j]) - t - t;
}

elem subtree_sum(int i) { return query_aib<subtree_aib>(last_ap[i]) - query_aib<subtree_aib>(first_ap[i]); }

void set_value(int i, elem x) {
    elem delta = x - curr_value[i], zero = {};
    curr_value[i] = x;
    add_aib<subtree_aib>(first_ap[i], delta);
    add_aib<chain_aib>(first_ap[i], delta);
    add_aib<chain_aib>(last_ap[i], zero - delta);
}

void dfs(int curr) {
    first_ap[curr] = curr_time;
    last_ap[curr] = curr_time;
    sz[curr] = 1;
    euler[curr_time++] = curr;

    for (auto next : fii[curr]) {
        tt[next] = curr;
        fii[next].erase(find(begin(fii[next]), end(fii[next]), curr));
        adanc[next] = adanc[curr] + 1;
        dfs(next);
        sz[curr] += sz[next];
        euler[curr_time] = curr;
        last_ap[curr] = curr_time++;
    }
}

map<int, int> lens[maxn] = {};

void update(int x, int y, int z) {
    if (tt[x] == y) swap(x, y);

    // fiecare muchie e "numarata" la fiul sau.
    set_value(y, elem{int((ll)z * (n - sz[y]) % mod), int((ll)z * sz[y] % mod * (n - sz[y]) % mod),
                      int((ll)z * sz[y] % mod)});
}

int query(int x, int y) {
    int l = lca(x, y);
    elem everything = subtree_sum(0), my_subtree = subtree_sum(l), my_chain = chain_sum(x, y);
    elem hi_elem = everything - my_subtree;
    elem mid_elem = everything - my_chain;
    elem lo_elem = my_subtree - my_chain;

    ll chain_len = adanc[x] + adanc[y] - 2 * adanc[l];

    return (mid_elem.mid + (hi_elem.up + lo_elem.down) * (chain_len - 1)) % mod;
}

int main() {
//    ifstream f("zelda.in");
//    ofstream g("zelda.out");
    istream& f(cin);
    ostream& g(cout);

    f >> n;

    for (int i = 0, x, y, z; i < n - 1; ++i) {
        f >> x >> y >> z;
        fii[x].emplace_back(y);
        fii[y].emplace_back(x);
        lens[x][y] = lens[y][x] = z;
    }

    dfs(1);
    build_rmq();

    for (int i = 1; i <= n; ++i)
        for (auto t : lens[i]) update(i, t.first, t.second);

    int q;
    f >> q;

    while (q--) {
        int t;
        f >> t;

        if (t == 0) {
            int x, y, t;
            f >> x >> y >> t;
            update(x, y, t);
        }

        else {
            int x, y;
            f >> x >> y;
            g << query(x, y) << '\n';
        }
    }
}
