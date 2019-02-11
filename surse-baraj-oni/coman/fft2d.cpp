#include <stdio.h>
#include <algorithm>
#define MAXT 100000

struct black{
    int h, x;
    long long up, down;
} v[1 + MAXT];
bool cmp(black A, black B){return A.h < B.h;}

long long w[16][1 << 15];
int bad[16][1 << 15];
int main(){
    FILE*fi,*fo;
    fi = fopen("fft2d.in","r");
    fo = fopen("fft2d.out","w");

    int f, t;
    fscanf(fi,"%d%d", &f, &t);
    for(int i = 1; i <= t; i++) fscanf(fi,"%d%d", &v[i].h, &v[i].x);
    if(f <= 16){
        for(int i = 1; i <= t; i++) bad[v[i].h][v[i].x] = i, v[i].up = (1LL << v[i].h);
        for(int x = 0; x <= (1 << (f - 1)) - 1; x++){
            w[f - 1][x] = 1;
            if(bad[f - 1][x]) v[bad[f - 1][x]].down = w[f - 1][x];
        }
        for(int h = f - 2; h >= 0; h--){
            for(int x = 0; x <= (1 << (f - 1)) - 1; x++){
                if(!bad[h + 1][x]) w[h][x] += w[h + 1][x];
                if(!bad[h + 1][x ^ (1 << (f - h - 2))]) w[h][x] += w[h + 1][x ^ (1 << (f - h - 2))];
                if(bad[h][x]) v[bad[h][x]].down = w[h][x];
            }
        }
        long long ans = (1LL << (2 * f - 2));
        for(int i = 1; i <= t; i++)
            ans -= v[i].up * v[i].down;
        fprintf(fo,"%lld", ans);
    }
    else{
        std::sort(v + 1, v + t + 1, cmp);
        long long ans = (1LL << (2 * f - 2));
        for(int i = t; i >= 1; i--){
            v[i].up = (1LL << v[i].h);
            v[i].down = (1LL << (f - v[i].h - 1));
            for(int j = i + 1; j <= t; j++) if(v[j].h > v[i].h){
                if((v[i].x ^ v[j].x) < (1 << (f - v[i].h - 1)) &&
                        ((v[i].x ^ v[j].x) & ((1 << (f - v[j].h - 1)) - 1)) == 0){
                    v[i].down -= v[j].down;
                }
            }
            ans -= v[i].up * v[i].down;
        }
        fprintf(fo,"%lld", ans);
    }

    fclose(fi);
    fclose(fo);
    return 0;
}
