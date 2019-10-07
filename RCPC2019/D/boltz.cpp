#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

FILE *f = fopen("boltz.in","r");
FILE *g = fopen("boltz.out","w");

const int MAXNR = 1000;

int n;
int p[10];
int q[10];
double rp[10];
double rq[10];
double dp[2][1 << 8][2][8];///probabilitatea maxima de a castiga

int prv[1 << 8][8];
int nxt[1 << 8][8];

bool boltz(int x) {
    if(x % 7 == 0) {
        return true;
    }

    while(x) {
        if(x % 10 == 7) {
            return true;
        }
        x /= 10;
    }

    return false;
}

int main() {

    for(int conf = 1; conf < (1 << 8); conf++) {
        for(int i = 0; i < 8; i++) {
            int p = (i + 7) % 8;
            while(((conf >> p) & 1) == 0) {
                p = (p + 7) % 8;
            }
            prv[conf][i] = p;
            int n = (i + 1) % 8;
            while(((conf >> n) & 1) == 0) {
                n = (n + 1) % 8;
            }
            nxt[conf][i] = n;
        }
    }

    fscanf(f,"%d",&n);

    for(int i = 0; i < n; i++) {
        fscanf(f,"%d %d",&p[i],&q[i]);
        rp[i] = p[i] / double(100);
        rq[i] = q[i] / double(100);
    }

    double ans = 0;

    for(int st = 0; st < n; st++) {
        memset(dp,0,sizeof(dp));
        dp[MAXNR & 1][1 << st][0][st] = 1;
        dp[MAXNR & 1][1 << st][1][st] = 1;

        for(int pas = (MAXNR - 1),l = (MAXNR - 1) & 1; pas; pas--,l ^= 1) {
            for(int conf = 0; conf < (1 << 8); conf++) {
                for(int sens = 0; sens < 2; sens++) {
                    for(int i = 0; i < n; i++) {
                        dp[l][conf][sens][i] = 0;
                        if(((conf >> st) & 1) == 0) {
                            continue;
                        }
                        if(((conf >> i) & 1) == 0) {
                            continue;
                        }
                        int prv_juc = prv[conf][i];
                        int nxt_juc = nxt[conf][i];
                        if(prv_juc == i) {
                            dp[l][conf][sens][i] = 1;
                            continue;
                        }
                        if(sens == 1) {
                            swap(prv_juc,nxt_juc);
                        }
                        if(boltz(pas)) {
                            dp[l][conf][sens][i] = (1 - rq[i]) * dp[l ^ 1][conf][!sens][prv_juc] + rq[i] * dp[l ^ 1][conf ^ (1 << i)][sens][nxt_juc];
                        }
                        else {
                            dp[l][conf][sens][i] = (1 - rp[i]) * dp[l ^ 1][conf][sens][nxt_juc] + rp[i] * dp[l ^ 1][conf ^ (1 << i)][sens][nxt_juc];
                        }
                    }
                }
            }
        }
        ans = max(ans,dp[1][(1 << n) - 1][0][0]);
    }

    fprintf(g,"%.3f",ans * 100);

    fclose(f);
    fclose(g);

    return 0;
}
