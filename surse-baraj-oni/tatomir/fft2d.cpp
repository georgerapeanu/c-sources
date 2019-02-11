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

const int maxF = 18;
const int maxVal = 1 << maxF;
const int maxT = 2018;

ll F, T, ss, dd, i, j, x, y, p, limit, bit;
vector< pair<ll, ll> > black;
ll dp[2][maxVal];

vector<int> list[maxT];
ll cnt[maxT][maxT];

bool arc(pair<ll, ll> a, pair<ll, ll> b) {
    int i;

    for (i = 0; i < F - 1 - a.first && i < F - 1 - b.first; i++)
        if (((a.second >> i) & 1) != ((b.second >> i) & 1))
            return false;

    for (i = 0; i < a.first && i < b.first; i++)
        if (((a.second >>  (F - 1 - i) ) & 1) != ((b.second >> (F - 1 - i)) & 1))
            return false;

    return true;
}

void smart() {
    int i, j;
    ll ans = 1LL << (2 * F - 2);

    for (i = 0; i < black.size(); i++) {
        for (j = i + 1; j < black.size(); j++) {
            if (arc(black[i], black[j])) {
                list[i].pb(j);
            }
        }
    }

    printf("%lld", ans);
}

void bulan() {
    ll ans = 1LL << (2 * F - 2);

    for (i = 0; i < black.size(); i++)
        ans -= 1LL << (F - 1);

    printf("%lld", ans);
}

int main()
{
    freopen("fft2d.in", "r", stdin);
    freopen("fft2d.out", "w", stdout);

    scanf("%lld%lld", &F, &T);
    for (i = 1; i <= T; i++) {
        scanf("%lld%lld", &x, &y);
        black.pb(mp(x, y));
    }

    sort(black.begin(), black.end());

    if (F < 18) {

        p = 0;
        limit = 1 << (F - 1);

        ss = 0; dd = 1;
        for (i = 0; i < limit; i++) dp[ss][i] = 1;

        while (p < black.size()) {
            if (black[p].first != 0) break;
            dp[ss][black[p].second] = 0;
            p++;
        }

        for (i = 1; i < F; i++) {
            memcpy(dp[dd], dp[ss], sizeof(dp[dd]));
            bit = 1 << (F - i - 1);

            for (j = 0; j < limit; j++)
                dp[dd][j ^ bit] += dp[ss][j];

            while (p < black.size()) {
                if (black[p].first != i) break;
                dp[dd][black[p].second] = 0;
                p++;
            }

            swap(ss, dd);
        }

        ll ans = 0;
        for (i = 0; i < limit; i++) ans += dp[ss][i];

        printf("%lld", ans);

    } else {
        bulan();
        //smart();
    }




    return 0;
}
