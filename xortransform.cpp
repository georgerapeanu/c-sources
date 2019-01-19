#include <cstdio>

using namespace std;

FILE *f = fopen("xortransform.in","r");
FILE *g = fopen("xortransform.out","w");

const int MAX_LOG = 21;
const int MASK = (1 << (MAX_LOG + 1)) - 1;

int n,m,q;
int dp[1<<(MAX_LOG + 1)];

int main() {

    fscanf(f,"%d %d %d",&n,&m,&q);

    for(int i = 0; i < n; i++) {
        for(int j = 0; j < m; j++) {
            int val;
            fscanf(f,"%d",&val);
            dp[i | j] ^= val;
        }
    }

    for(int i = 0; i <= MAX_LOG; i++) {
        for(int j = 0; j <= MASK; j++) {
            if(((j >> i) & 1) == 1) {
                dp[j] ^= dp[j ^ (1 << i)];
            }
        }
    }

    int ans = 0;

    while(q--) {
        int val;
        fscanf(f,"%d",&val);
        val ^= ans;

        fprintf(g,"%d\n",ans = dp[MASK & val]);
    }

    fclose(f);
    fclose(g);

    return 0;
}
