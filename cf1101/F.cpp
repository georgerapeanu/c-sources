#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

const int NMAX = 400;
const int QMAX = 25e4;
const int LEN = 1e4;
const long long inf = 1LL << 60;

char buff[LEN];
int ind = LEN - 1;

int i32() {
    int ans = 0;

    while(buff[ind] < '0' || buff[ind] > '9') {
        if(++ind >= LEN) {
            ind = 0;
            fread(buff,1,LEN,stdin);
        }
    }

    while(!(buff[ind] < '0' || buff[ind] > '9')) {
        ans = ans * 10 + (buff[ind] - '0');
        if(++ind >= LEN) {
            ind = 0;
            fread(buff,1,LEN,stdin);
        }
    }

    return ans;
}

int n,q;
int a[NMAX + 5];

long long dp[2][NMAX + 5][NMAX + 5];///[j,k] in i groups
long long pref_sum[NMAX + 5];

vector<pair<pair<int,int>,int> > v[NMAX + 5];

int main() {
    n = i32();
    q = i32();


    for(int i = 1; i <= n; i++) {
        a[i] = i32();
        pref_sum[i] = a[i];
    }

    for(int j = 1; j <= n; j++) {
        for(int k = 1; k <= j; k++) {
            dp[1][j][k] = inf;
        }
        for(int k = j + 1; k <= n; k++) {
            dp[1][j][k] = a[k] - a[j];
        }
    }

    long long ans = 0;

    while(q--) {
        int s,f,c,r;
        s = i32();
        f = i32();
        c = i32();
        r = i32();
        v[min(f - s,r + 1)].push_back({{s,f},c});
    }

    for(int i = 2,l = 0; i <= n; i++,l ^= 1) {
        for(int j = 1; j <= n; j++) {
            int pref = j;
            for(int k = 1; k <= j; k++) {
                dp[l][j][k] = inf;
            }
            for(int k = j + 1; k <= n; k++) {
                while(pref + 1 < k && dp[l ^  1][j][pref + 1] <= pref_sum[k] - pref_sum[pref + 1]) {
                    pref++;
                }

                dp[l][j][k] = min(pref_sum[k] - pref_sum[pref], dp[l ^  1][j][pref + 1]);
                dp[l][j][k] = min(dp[l][j][k],dp[l ^ 1][j][k]);
            }
        }

        for(auto it:v[i]) {
            ans = max(ans,1LL * dp[l][it.first.first][it.first.second] * it.second);
        }
    }

    for(auto it:v[1]) {
        ans = max(ans,1LL * (a[it.first.second] - a[it.first.first]) * it.second);
    }

    printf("%lld\n",ans);

    return 0;
}
