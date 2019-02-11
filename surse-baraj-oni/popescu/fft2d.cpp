#include <bits/stdc++.h>
using namespace std;

int F, T;
int f[22][500000];
long long d[22][550000];
long long Sol = 0;
inline void dfs(int h, int x){
    int h2 = h + 1, x2 = x;
    if(f[h2][x2] == 0){
        d[h2][x2] += d[h][x];
    }
    x2 = x ^ (1 << (F - h - 2));
    if(f[h2][x2] == 0){
        d[h2][x2] += d[h][x];
    }
}
int main()
{
    freopen("fft2d.in", "r", stdin);
    freopen("fft2d.out", "w", stdout);
    scanf("%d%d", &F, &T);
    int h, x;
    for(int i = 1; i <= T ; ++i){
        scanf("%d%d", &h, &x);
        f[h][x] = 1;
    }
    for(int h = 0; h < F - 1 ; ++h)
    for(int i = 0; i < (1 << (F - 1)) ; ++i){
        if(f[h][i]) continue ;
        if(h == 0)d[0][i] = 1;
        dfs(h, i);
    }
    long long Sol = 0;
    for(int i = 0; i < (1 << (F - 1)) ; ++i) Sol += d[F - 1][i];
    printf("%lld", Sol);
    return 0;
}
