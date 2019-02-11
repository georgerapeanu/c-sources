#include <iostream>
#include <cstring>
#include <cmath>
#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

#define pb push_back
#define mp make_pair
#define ll long long

const int maxN = 200011;
const int bts = 30;
const ll mod = 1000000007;
const int def = 400000;

class Buffer {
    public:
        Buffer(string name, int _dim) {
            freopen(name.c_str(), "r", stdin);
            dim = _dim;
            data.resize(dim + 11);
            refill();
        }

        Buffer& operator>>(int& dest) {
            while (!is_digit(data[pos]))
                if (++pos == dim)
                    refill();

            dest = 0;
            while (is_digit(data[pos])) {
                dest = dest * 10 + data[pos] - '0';
                if (++pos == dim)
                    refill();
            }

            return *this;
        }

    private:
        int dim, pos;
        vector<char> data;

        bool is_digit(char c)  {
            return '0' <= c && c <= '9';
        }

        void refill() {
            pos = 0;
            memset(&data[0], 0, dim);
            fread(&data[0], 1, dim, stdin);
        }
};

int n, i, x, y;
int dad[maxN], depth[maxN];
int cnt[maxN][bts + 2][2];
vector<int> list[maxN];
vector< pair<int, int> > ord;
bool on[maxN];

ll p2[def + 11];
ll ans;

int Find(int x) {
    if (dad[x] == x) return x;
    dad[x] = Find(dad[x]);
    return dad[x];
}

bool Merge(int x, int y) {
    static int i;

    x = Find(x);
    y = Find(y);

    if (x == y) return false;

    if (depth[x] < depth[y]) swap(x, y);
    dad[y] = x;
    depth[x] = max(depth[x], depth[y] + 1);

    for (i = 0; i <= bts; i++) {
        cnt[x][i][0] += cnt[y][i][0];
        cnt[x][i][1] += cnt[y][i][1];
    }

    return true;
}

void add(ll& a, ll b) {
    a += b;
    if (a >= mod) a -= mod;
}

void solve(int R, int val) {
    int i, to, fto, a, b, p, here;
    ll act = 0;

    on[R] = true;
    dad[R] = R;
    depth[R] = 0;
    for (i = 0; i <= bts; i++)
        cnt[R][i][(val >> i) & 1] = 1;

    for (i = 0; i < list[R].size(); i++) {
        to = list[R][i];
        if (!on[to]) continue;
        fto = Find(to);

        for (p = 0; p <= bts; p++) {
            a = cnt[fto][p][0];
            b = cnt[fto][p][1];
            here = (val >> p) & 1;

            if (b == 0) {
                if (here == 1) {
                    add(act, mod - p2[a + p]);
                    add(act, p2[p]);
                }
            } else {
                add(act, mod - p2[a + b - 1 + p]);
                if (here == 1) add(act, p2[p]);
            }

            if (act >= mod) act -= mod;
        }

        Merge(R, fto);
    }

    R = Find(R);
    for (p = 0; p <= bts; p++) {
        a = cnt[R][p][0];
        b = cnt[R][p][1];
        here = (val >> p) & 1;

        if (b == 0) {
            if (here == 1) {
                add(act, p2[a + p]);
                add(act, mod - p2[p]);
            }
        } else {
            add(act, p2[a + b - 1 + p]);
            if (here == 1) add(act, mod - p2[p]);
        }
    }

    ans += act;
    ans %= mod;
}

int main()
{
    Buffer fin("countfefete.in", 1 << 20);
    freopen("countfefete.out", "w", stdout);

    fin >> n;
    for (i = 1; i <= n; i++) {
        fin >> x;
        ord.pb(mp(x, i));
    }
    for (i = 1; i < n; i++) {
        fin >> x >> y;
        list[x].pb(y);
        list[y].pb(x);
    }

    sort(ord.begin(), ord.end());
    reverse(ord.begin(), ord.end());

    p2[0] = 1;
    for (i = 1; i <= def; i++) p2[i] = (p2[i - 1] * 2) % mod;

    for (i = 0; i < ord.size(); i++) {
        solve(ord[i].second, ord[i].first);
    }

    printf("%lld", ans);


    return 0;
}
