#include <cstdio>
#include <cstdlib>
#include <map>
#include <algorithm>
#define ll long long

using namespace std;

const int MAXF = 30;
const int MAXT = (int) 1e5;

ll dp[17][(1 << 16) + 1];
map < pair <int, int>, bool > mp;

pair <int, int> v[MAXT + 1];
bool vis[MAXT + 1];

int f;

inline bool ok(int l1, int c1, int l2, int c2) {
    int i;
    if(l1 >= l2)
        return 0;
    for(i = f - 2; i > f - l1 - 2; i--) {
        if((c1 & (1 << i)) != (c2 & (1 << i)))
            return 0;
    }
    for(i = 0; i <= f - l2 - 2; i++) {
        if((c1 & (1 << i)) != (c2 & (1 << i)))
            return 0;
    }
    return 1;
}

ll dp1[MAXT + 1];

int main() {
    FILE *fi, *fout;
    int i, j, t, l, c;
    fi = fopen("fft2d.in" ,"r");
    fout = fopen("fft2d.out" ,"w");
    fscanf(fi,"%d %d " ,&f,&t);
    for(i = 1; i <= t; i++) {
        fscanf(fi,"%d %d " ,&v[i].first,&v[i].second);
    }
    if(f <= 16) {
        for(i = 1; i <= t; i++) {
            mp[v[i]] = 1;
        }
        for(i = f - 1; i >= 0; i--) {
            for(j = 0; j < (1 << (f - 1)); j++) {
                if(mp[make_pair(i, j)] == 0) {
                    if(i == f - 1)
                        dp[i][j] = 1;
                    else
                        dp[i][j] = dp[i + 1][j] + dp[i + 1][j ^ (1 << (f - i - 2))];
                }
                else
                    dp[i][j] = 0;
            }
        }
        ll ans = 0;
        for(i = 0; i < (1 << (f - 1)); i++) {
            ans += dp[0][i];
        }
        fprintf(fout,"%lld" ,ans);
    }
    else {
        sort(v + 1, v + t + 1);
        for(i = t; i >= 1; i--) {
            dp1[i] = (1LL << (f - v[i].first - 1));
            for(j = i + 1; j <= t; j++) {
                if(ok(v[i].first, v[i].second, v[j].first, v[j].second))
                    dp1[i] -= dp1[j];
            }
        }
        ll ans = 1LL * (1LL << (f - 1)) * (1LL << (f - 1));
        for(i = 1; i <= t; i++) {
            ans -= 1LL * dp1[i] * (1LL << v[i].first);
        }
        fprintf(fout,"%lld" ,ans);
    }
    fclose(fi);
    fclose(fout);
    return 0;
}
