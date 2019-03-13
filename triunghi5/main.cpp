#include <cstdio>
#include <algorithm>

using namespace std;

FILE *f = fopen("triunghi5.in","r");
FILE *g = fopen("triunghi5.out","w");

long long c,n,k;

long long v[50];

long long nv[50],len;

int main(){

    fscanf(f,"%lld %lld %lld",&c,&n,&k);

    for(long long i = 1;i <= n;i++){
        fscanf(f,"%lld",&v[i]);
    }

    sort(v + 1,v + 1 + n);

    if(c == 1){
        fprintf(g,"%lld ",v[1]);
        long long fst = v[1],snd = v[1];
        for(long long i = 1;i < k;i++){
            fprintf(g,"%lld ",snd);
            snd = fst + snd;
            fst = snd - fst;
        }
    }
    else{
        k -= n;

        if(1 + v[1] <= v[2] && k){
            nv[++len] = 1;
            k--;
            if(1 + 1 <= v[1] && k){
                nv[++len] = 1;
                k--;
            }
        }

        v[n + 1] = 1LL << 58;

        for(long long i = 1;i <= n + 1;i++){
            if(len == 0){
                nv[++len] = v[i];
                continue;
            }

            while(k && nv[len - 1] + nv[len] + nv[len] <= v[i] && nv[len - 1] + nv[len] <= v[i + 1] - v[i]){
                nv[len + 1] = nv[len - 1] + nv[len];
                len++;
                k--;
            }
            nv[++len] = v[i];
        }

        for(long long i = 1;i <= len;i++){
            fprintf(g,"%lld ",nv[i]);
        }
    }

    fclose(f);
    fclose(g);

    return 0;
}
