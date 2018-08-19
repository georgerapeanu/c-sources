#include <cstdio>
using namespace std;
FILE *f = fopen("9div.in","r");
FILE *g = fopen("9div.out","w");
int N;
bool E[100000];
int len,P[100000];
long long lgpow(long long b,long long e){
    long long p = 1;
    while(e){
        if(b > N){
            return (1e9) + 1;
        }
        if(e & 1){
            if(p * b > N){
                return (1e9) + 1;
            }
            p = p * b;
        }
        e >>= 1;
        b = b * b;
    }
    return p;
}
int main()
{
    fscanf(f,"%d",&N);
    for(int i = 2;1LL * i * i <= N;i++){
        if(!E[i]){
            P[++len] = i;
            for(int j = i * 2;1LL * j * j <= N;j += i){
                E[j] = 1;
            }
        }
    }
    long long rez = 0;
    int j = len;
    for(int i = 1;i <= len;i++){
        if(lgpow(P[i],8) <= (long long)N){
            rez++;
        }
        while(j >= i && 1LL * P[i] * P[i] * P[j] * P[j] > (long long)N){
            j--;
        }
        if(j > i){
            rez = rez + j - i;
        }
    }
    fprintf(g,"%lld",rez);
    fclose(f);
    fclose(g);
    return 0;
}
