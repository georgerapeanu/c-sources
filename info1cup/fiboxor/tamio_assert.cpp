#include <bits/stdc++.h>
using namespace std;
 
using ll = long long;
constexpr int perioada = 3 << 19;
 
int sp[perioada + 10];
 
void init(int q) {
    sp[2] = 1;
    for (int i = 3; i <= perioada; ++i)
        sp[i] = (sp[i - 1] + sp[i - 2]) % (1 << 20);
 
    for (int i = 1; i <= perioada; ++i)
        sp[i] ^= sp[i - 1];
}
 
ll pref(ll x) { return sp[perioada] * (x / perioada % 2) ^ sp[x % perioada]; }
 
int query(int k, ll a, ll b) {
    static int qs = 0;
    assert(++qs <= 1e6);
    assert(0 <= a && a <= b && b <= 1e18);
    return (pref(b + 1) ^ pref(a)) % (1 << k);
}
 
int main() {
    ifstream f("xorfibo.in");
    ofstream g("xorfibo.out");
 

    int q;
    f >> q;
    init(q);
 
    while (q--) {
        long long k, a, b;
        f >> k >> a >> b;
 
        g << query(k, a, b) << '\n';
    }
}
