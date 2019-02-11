#include <stdio.h>
#define MAXN 500000
#define MAXL 1000005
#define MOD1 666013
#define MOD2 666019

int V[1 + MAXL];
int m1[1 + MAXL], m2[1 + MAXL];
int p1[1 + MAXL], p2[1 + MAXL];
int main(){
    FILE*fi,*fo;
    fi = fopen("pscfft.in","r");
    fo = fopen("pscfft.out","w");

    int t;
    fscanf(fi,"%d", &t);
    p1[0] = p2[0] = 1;
    for(int i = 1; i <= 2 * MAXN; i++){
        p1[i] = (p1[i - 1] * 10) % MOD1;
        p2[i] = (p2[i - 1] * 10) % MOD2;
    }


    for(int z = 1; z <= t; z++){
        int n, s;
        fscanf(fi,"%d%d", &n, &s);
        int key1 = 0, key2 = 0;
        for(int i = 1; i <= n; i++){
            int x;
            fscanf(fi,"%d", &x);
            key1 = (key1 * 10 + x) % MOD1;
            key2 = (key2 * 10 + x) % MOD2;
        }
        int len = 1;
        V[1] = 0;
        while(s * len <= 2 * MAXN){
            for(int i = len + 1; i <= len * s; i++)
                V[i] = (V[i - len] + 1) % s;
            len *= s;
        }
        for(int i = len + 1; i <= 2 * MAXN; i++)
            V[i] = (V[i - len] + 1) % s;
        len = 2 * MAXN;

        for(int i = 1; i <= len; i++){
            m1[i] = (m1[i - 1] * 10 + V[i]) % MOD1;
            m2[i] = (m2[i - 1] * 10 + V[i]) % MOD2;
        }
        int ok = 0;
        for(int i = n; i <= 2 * MAXN && !ok; i++){
            int k1 = (1LL * m1[i] - 1LL * m1[i - n] * p1[n]) % (1LL * MOD1);
            if(k1 < 0) k1 += MOD1;
            int k2 = (1LL * m2[i] - 1LL * m2[i - n] * p2[n]) % (1LL * MOD2);
            if(k2 < 0) k2 += MOD2;
            if(k1 == key1 && k2 == key2) ok = i - n;
        }
        if(ok) fprintf(fo,"%d\n", ok);
        else fprintf(fo,"-1\n");
    }

    fclose(fi);
    fclose(fo);
    return 0;
}
