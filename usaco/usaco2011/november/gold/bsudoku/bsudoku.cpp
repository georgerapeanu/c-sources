#include <cstdio>
#include <algorithm>

using namespace std;

FILE *f = fopen("bsudoku.in","r");
FILE *g = fopen("bsudoku.out","w");

const int inf = 9 * 9 * 9;

int dp[10][1 << 9][1 << 3];
int a[10];
char c[15];
int cnt[1 << 9];

int main() {

    for(int i = 1; i <= 9; i++) {
        fgets(c + 1,12,f);
        for(int j = 1; j <= 9; j++) {
            a[i] |= ((int(c[j] - '0')) << (j - 1));
        }
    }

    for(int i = 0; i <= 9; i++) {
        for(int mask = 0; mask < (1 << 9); mask++) {
            cnt[mask] = (mask & 1) + cnt[mask >> 1];
            for(int mask2 = 0; mask2 < (1 << 3); mask2++) {
                dp[i][mask][mask2] = inf;
            }
        }
    }

    dp[0][0][0] = 0;


    for(int i = 0; i <= 8; i++) {
        if(i % 3 == 0) {
            for(int mask = 0; mask < (1 << 9); mask++) {
                for(int mask2 = 1; mask2 < (1 << 3); mask2++) {
                    dp[i][mask][mask2] = inf;
                }
            }
        }

        for(int mask = 0; mask < (1 << 9); mask++) {
            for(int mask2 = 0; mask2 < (1 << 3); mask2++) {
                for(int target = 0; target < (1 << 9); target++) {
                    if(cnt[target ^ mask] & 1) {
                        continue;
                    }
                    int cost = dp[i][mask][mask2] + cnt[mask ^ target ^ a[i + 1]];
                    int nmask2 = (cnt[target & 7] & 1) + (cnt[target & 56] & 1) * 2 + (cnt[target & 448] & 1) * 4;
                    dp[i + 1][target][nmask2] = min(dp[i + 1][target][nmask2],cost);
                }
            }
        }
    }

    fprintf(g,"%d\n",dp[9][0][0]);

    fclose(f);
    fclose(g);

    return 0;
}
