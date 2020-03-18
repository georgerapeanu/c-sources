#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

FILE *f = fopen("sunmihai.in","r");
FILE *g = fopen("sunmihai.out","w");

const int NMAX = 1e5;
const int VMAX = 100;
const int inf = 2e7;

const int LEN = 1 << 13;
char buff[LEN];
int ind = LEN - 1;

int i32() {
    int ans = 0;

    while(buff[ind] < '0' || buff[ind] > '9') {
        if(++ind >= LEN) {
            ind = 0;
            fread(buff,1,LEN,f);
        }
    }

    while(!(buff[ind] < '0' || buff[ind] > '9')) {
        ans = ans * 10 + (buff[ind] - '0');
        if(++ind >= LEN) {
            ind = 0;
            fread(buff,1,LEN,f);
        }
    }

    return ans;
}

int n,a,b,c;
int dp[2][VMAX + 1];
int dom[NMAX + 5][2];

int main() {

    n = i32();
    a = i32();
    b = i32();
    c = i32();

    for(int i = 1; i <= n; i++) {
        for(int x = 0; x < 2; x++) {
            dom[i][x] = i32();
        }
    }

    for(int i = 1; i <= VMAX; i++) {
        dp[1][i] = inf;
    }
    dp[1][dom[1][1]] = 0;
    dp[1][dom[1][0]] = min(dp[1][dom[1][0]],a);

    for(int i = 2,l = 0; i <= n; i++,l ^= 1) {
        for(int h = 1; h <= VMAX; h++) {
            if(i == n) {
                dp[l][h] = inf;
            }
            else {
                dp[l][h] = min(inf,dp[l ^ 1][h] + b);
            }
        }
        for(int h = 1; h <= VMAX; h++) {
            dp[l][dom[i][1]] = min(dp[l][dom[i][1]],dp[l ^ 1][h] + (h != dom[i][0]) * c);
            dp[l][dom[i][0]] = min(dp[l][dom[i][0]],dp[l ^ 1][h] + (h != dom[i][1]) * c + a);
        }
    }

    int ans = inf;

    for(int h = 1; h <= VMAX; h++) {
        ans = min(ans,dp[n & 1][h]);
    }

    fprintf(g,"%d\n",ans);

    fclose(f);
    fclose(g);

    return 0;
}
