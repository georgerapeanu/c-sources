#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")
#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
using namespace std;

FILE *f = fopen("rogvaiv.in","r");
FILE *g = fopen("rogvaiv.out","w");

const int NMAX = 5e4;
const int LEN = 7;
int MOD;

const char p1[] = "ABCDEFG";
const char p2[] = "GFEDCBA";
const char alpha[] = "ABCDEFG";

int c,n;
vector<pair<int,int> > to[LEN + 5][LEN + 5];
int dp[2][LEN + 5][LEN + 5];

void propag(int j,int k,char c) {
    int jp = (j == LEN ? LEN:(c == p1[j] ? j + 1:(c == p1[0] ? 1:0)));
    int kp = (k == LEN ? LEN:(c == p2[k] ? k + 1:(c == p2[0] ? 1:0)));

    to[j][k].push_back({jp,kp});
}

int main() {

    fscanf(f,"%d %d %d",&c,&n,&MOD);

    dp[0][0][0] = 1;

    for(int j = 0; j <= LEN; j++) {
        for(int k = 0; k <= LEN; k++) {
            for(char c = 'A'; c <= 'G'; c++) {
                propag(j,k,c);
            }
        }
    }

    for(int i = 0,l = 0; i < n; i++,l ^= 1) {
        memset(dp[l ^ 1],0,sizeof(dp[l ^ 1]));
        for(int j = 0; j <= LEN; j++) {
            for(int k = 0; k <= LEN; k++) {
                for(auto it:to[j][k]) {
                    dp[l ^ 1][it.first][it.second] += dp[l][j][k];
                    if(dp[l ^ 1][it.first][it.second] >= MOD) {
                        dp[l ^ 1][it.first][it.second] -= MOD;
                    }
                }
            }
        }
    }

    int ans = 0;

    for(int j = 0; j <= LEN; j++) {
        for(int k = 0; k <= LEN; k++) {
            if(j == LEN) {
                ans += dp[n & 1][j][k];
                if(ans >= MOD) {
                    ans -= MOD;
                }
            }
            else if(k == LEN && c == 2) {
                ans += dp[n & 1][j][k];
                if(ans >= MOD) {
                    ans -= MOD;
                }
            }
        }
    }

    fprintf(g,"%d\n",ans);

    fclose(f);
    fclose(g);

    return 0;
}
