#include <cstdio>

using namespace std;

FILE *f = fopen("turnuri.in","r");
FILE *g = fopen("turnuri.out","w");

const int LGMAX = 20;
const int NMAX = 15;

int n,k;
long long dp[1 << LGMAX];
int l[NMAX + 5];

int main(){

    fscanf(f,"%d %d",&n,&k);

    for(int i = 1;i <= n;i++){
        fscanf(f,"%d",&l[i]);
    }

    dp[0] = 1;

    for(int i = 1;i <= n;i++){
        for(int conf = (1 << l[i]) - 1;conf >= 0;conf--){
            for(int j = 0;j < l[i];j++){
                if(((conf >> j) & 1) == 0){
                    dp[conf ^ (1 << j)] += dp[conf];
                }
            }
        }
    }

    long long ans = 0;

    for(int conf = 0;conf < (1 << l[n]);conf++){
        int tmp = conf;
        int cnt = 0;

        while(tmp){
            tmp -= (-tmp) & tmp;
            cnt++;
        }

        ans += dp[conf] * (cnt == k);
    }

    fprintf(g,"%lld\n",ans);

    fclose(f);
    fclose(g);

    return 0;
}
