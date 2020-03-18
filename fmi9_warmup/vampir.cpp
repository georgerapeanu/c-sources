#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

FILE *f = fopen("vampir.in","r");
FILE *g = fopen("vampir.out","w");

const int MOD = 1e9 + 7;

int lgpow(int b,int e) {
    int p = 1;

    while(e) {
        if(e & 1) {
            p = 1LL * p * b % MOD;
        }
        b = 1LL * b * b % MOD;
        e >>= 1;
    }

    return p;
}

int main() {

    int c,l;

    fscanf(f,"%d %d",&c,&l);

    l /= 2;

    if(l % 2 == 1) {
        fprintf(g,"-1\n");
        return 0;
    }
    else {
        if(c == 1) {
            int cnt = 0;
            for(int i = 2; i <= l; i += 2) {
                if(l % i == 0) {
                    cnt++;
                }
            }
            fprintf(g,"%d\n",cnt);
            for(int i = 2; i <= l; i += 2) {
                if(l % i == 0) {
                    fprintf(g,"%d ",i);
                }
            }

        }
        else {
            l /= 2;
            int ans = 1;
            int fact = 1;
            for(int i = 1; i < l; i++) {
                fact = 1LL * fact * i % MOD;
            }
            ans = 1LL * fact * fact % MOD;
            for(int i = l; i < 2 * l; i++) {
                fact = 1LL * fact * i % MOD;
            }
            ans = 1LL * ans * lgpow(fact,MOD - 2) % MOD;
            fprintf(g,"%d\n",ans);
        }
    }

    fclose(f);
    fclose(g);

    return 0;
}
