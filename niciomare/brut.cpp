#include <cstdio>
#include <algorithm>

using namespace std;

FILE *f = fopen("niciomare.in","r");
FILE *g = fopen("niciomare.ok","w");

const int NMAX = 1e5;
const int KMAX = 100;
const int SMAX = 1e8;

int n,k,s;
int v[NMAX + 5];
long long dp[NMAX + 5];
long long pref_sum[NMAX + 5];

int main() {

    fscanf(f,"%d %d %d",&n,&k,&s);

    for(int i = 1; i <= n; i++) {
        fscanf(f,"%d",&v[i]);
        pref_sum[i] = pref_sum[i - 1] + v[i];
    }

    for(int h = 1; h <= k; h++) {
        for(int i = n; i; i--) {
            for(int j = i - 1; j >= 0; j--) {
                if(pref_sum[i] - pref_sum[j] > s) {
                    break;
                }
                dp[i] = max(dp[i],dp[j] + 1LL * (pref_sum[i] - pref_sum[j]) * (pref_sum[i] - pref_sum[j]));
            }
        }
        for(int i = 1; i <= n; i++) {
            dp[i] = max(dp[i - 1],dp[i]);
        }
    }

    fprintf(g,"%lld\n",dp[n]);

    fclose(f);
    fclose(g);

    return 0;
}
