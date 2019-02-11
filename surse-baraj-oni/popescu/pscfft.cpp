#include <bits/stdc++.h>
using namespace std;

int n, t, s;
int p[500005], a[500005], k[500005];
bool ok[500005];
const int MOD = 1e9 + 7;
inline int lgput(int x, int p){
    int aux = x, ans = 1;
    for(int i = 0; (1 << i) <= p ; ++i){
        if((p & (1 << i))) ans = (1LL * ans * aux) % MOD;
        aux = (1LL * aux * aux) % MOD;
    }
    return ans;
}
int am[4][4], b[4][4];
inline void inm(int am[4][4], int B[4][4], int C[4][4]){
    for(int i = 0; i <= 1 ; ++i)
        for(int j = 0; j <= 1 ; ++j)
            for(int k = 0; k <= 1 ; ++k)
            C[i][j] = (C[i][j] + 1LL * am[i][k] * B[k][j]) % MOD;
}
inline void lgmatrix(int put){
    int aux[4][4];
    memset(aux, 0, sizeof(aux));
    for(int i = 0; (1 << i) <= put ; ++i){
        if((1 << i) & put){
            memset(aux, 0, sizeof(aux));
            inm(am, b, aux);
            memcpy(am, aux, sizeof(aux));
        }
        memset(aux, 0, sizeof(aux));
        inm(b, b, aux);
        memcpy(b, aux, sizeof(aux));

    }
}
int main()
{
    freopen("pscfft.in", "r", stdin);
    freopen("pscfft.out", "w", stdout);
    scanf("%d", &t);
    while(t--){
        scanf("%d%d", &n, &s);
        scanf("%d", &a[1]);
        for(int i = 2; i <= n ; ++i){
            scanf("%d", &a[i]);
        }
        bool ver = 0;
        int scad = 0, cat = 0, P = 1;
        while(n >= 1){
            if(n == 1) {
                int Sol = (1LL * P * a[1]) % MOD;
                Sol = (Sol + cat) % MOD;
                printf("%d\n", Sol);
                break ;
            }
            if(n == 2 && (a[1] + 1) % s != a[2]){
                int dif = a[2] - a[1];
                if(dif <= 0) dif = dif + s;
                --dif;
                a[1] = a[2] - 1;
                if(a[1] < 0) a[1] += s;

                am[0][0] = 0; am[0][1] = 0;
                am[1][0] = s; am[1][1] = 1;
                b[0][0] = s; b[0][1] = 1;
                b[1][1] = 1;
                lgmatrix(dif - 1);
                cat = (cat + (1LL * (s - 1) * P * am[1][1]) % MOD) % MOD;
                if(cat < 0) cat += MOD;

                int NP = lgput(s, dif);
                P = (1LL * NP * P) % MOD;

            }
            for(int i = 2; i <= n ; ++i){
                ok[i] = 0; k[i] = 0;
                int Last = a[i] - 1;
                if(Last < 0) Last += s;
                if(Last != a[i - 1]) ok[i] = 1;
                else k[i] = k[i - 1] + 1;
            }
            int NR = 0, found = 0, N = 0, nr, w = 1;
            for(int i = 2; i <= n ; ++i){
                if(ok[i]){
                    int Last = i - 1;
                    if(Last == N) continue ;
                    if(k[Last] < min(s - 1, i - 2)){ver = 1; break ;}
                    int nr = 0;
                    while(Last > N){
                        if(NR == 0){
                            int r = s - k[Last] - 1;
                            if(r < 0) r = 0;
                            cat = cat + (1LL * r * P) % MOD;
                            if(cat >= MOD) cat -= MOD;
                        }
                        p[++nr] = a[Last] + 1;
                        if(p[nr] >= s) p[nr] -= s;
                        Last = Last - s;
                    }
                    N = i - 1;
                    for(int i = nr; i >= 1 ; --i)
                        a[++NR] = p[i];
                }
            }
            if(ver == 1){break ;}
            if(N < n) {
                if(NR > 0) a[++NR] = a[N + 1];
                else{
                    int r = a[n] - a[1];
                    if(r > 0){
                        int r = a[1];
                        cat = cat + (1LL * r * P) % MOD;
                        printf("%d\n", cat);
                        break ;
                    }
                    else{
                        int aux = a[1];
                        a[++NR] = a[n] + 1;
                        if(a[NR] >= s) a[NR] -= s;
                        int r = s - n;
                        cat = cat + (1LL * r * P) % MOD;
                    }
                }
            }
            n = NR;
            P = (1LL * P * s) % MOD;
        }
        if(ver == 1){printf("-1\n"); continue ;}
    }
    return 0;
}
