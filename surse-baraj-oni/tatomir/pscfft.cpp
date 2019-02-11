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

const int maxN = 500011;
const ll moddo = 1000000007;

const int def = 500000;

int t, ti;
ll n, mod, i, x;
vector<ll> v;
vector<pair<ll, ll> > data, aux;
vector<ll> wh;

int work[maxN];
int pr[maxN];
int br[maxN];

inline ll nxt(ll x) {
    if (x + 1 < mod) return x + 1;
    return 0;
}

ll old_solve() {
    int i;
    ll last, act;

    if (v.size() == 1) return v[0];

    last = -7;
    data.clear();
    for (i = 0; i < v.size(); i++) {
        act = v[i];

        if (nxt(last) == act) {
            data[data.size() - 1].second++;
        } else {
            data.pb(mp(act, 1));
        }

        last = act;
    }

    aux = data;
    data.clear();
    for (i = 0; i < aux.size(); i++) {
        if (aux[i].second <= mod) {
            data.pb(aux[i]);
        } else {
            if (i == 0) {
                data.pb(mp(aux[i].first, aux[i].second - mod));
                data.pb(mp( (aux[i].first + aux[i].second - mod) % mod, mod ));
            } else {
                data.pb(mp(aux[i].first, mod));
                data.pb(mp(aux[i].first, aux[i].second - mod));
            }
        }
    }

    if (data.size() == 1) return data[0].first;

    if (data.size() == v.size()) return -1;


    for (i = 1; i + 1 < data.size(); i++)
        if (data[i].second != mod)
            return -1;

    v.clear();
    v.pb((mod + data[0].first - (mod - data[0].second)) % mod);
    for (i = 1; i < data.size(); i++)
        v.pb(data[i].first);

    ll ans = old_solve();
    if (ans == -1) return -1;

    ans = (ans * mod + (mod - data[0].second)) % moddo;
    return ans;
}

ll solve() {
    int i;
    ll dif_max, dif, ans, add, sum, need;

    if (v.size() == 1) return v[0];

    dif_max = 0;
    for (i = 1; i < v.size(); i++) {
        dif = (v[i] - v[i - 1] - 1 +  2 * mod);
        while (dif > mod) dif -= mod;
        dif_max = max(dif_max, dif);
    }

    wh.clear();
    for (i = 1; i < v.size(); i++) {
        dif = (v[i] - v[i - 1] - 1 +  2 * mod);
        while (dif > mod) dif -= mod;
        if (dif == dif_max) wh.pb(i);
    }

    if (dif_max == 0) {

    } else {
        ans = 0; add = 1;
        sum = 0;

        for (i = 1; i <= dif_max; i++) {
            ans = (ans * mod + mod - 1) % moddo;
            add = (add * mod) % moddo;

            sum += mod - 1;
            sum %= mod;
        }

        need = (v[0] - sum) % mod;
    }
}

ll brute() {
    ll i, u, sz;

    for (i = 1; i <= n; i++) work[i] = v[i - 1];

    pr[1] = u = 0;
    for (i = 2; i <= n; i++) {
        while (u != 0 && work[i] != work[u + 1]) u = pr[u];
        if (work[i] == work[u + 1]) u++;
        pr[i] = u;
    }

    sz = 1;
    while (sz < def) {
        for (i = sz + 1; i <= sz * mod && i <= def; i++)
            br[i] = (br[i - sz] + 1) % mod;

        sz = min(1LL * def, sz * mod);
    }

    u = 0;
    for (i = 1; i <= def; i++) {
        while (u != 0 && work[u + 1] != br[i]) u = pr[u];
        if (work[u + 1] == br[i]) u++;
        if (u == n) {
            return i - n;
        }
    }

    return -1;
}

int main()
{
    freopen("pscfft.in", "r", stdin);
    freopen("pscfft.out", "w", stdout);

    scanf("%d", &t);
    for (ti = 1; ti <= t; ti++) {
        scanf("%lld%lld", &n, &mod);
        v.clear();
        for (i = 1; i <= n; i++) {
            scanf("%lld", &x);
            v.pb(x);
        }

        ll ans = brute();

        if (t <= 20 && mod <= 4) {
            printf("%lld\n", ans);
            continue;
        }

        if (ans != -1) {
            printf("%lld\n", ans);
            continue;
        }

        ans = old_solve();
        printf("%lld\n", ans);
    }

    return 0;
}
