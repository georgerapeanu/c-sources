#include <cstdio>
using namespace std;
FILE *f = fopen("dreptunghi.in","r");
FILE *g = fopen("dreptunghi.out","w");
long long gcd(long long N,long long M){
    if(!M){
        return 0LL;
    }
    return gcd(M,N % M) + M * (N / M);
}
long long N,M;
int main()
{
    fscanf(f,"%lld %lld",&N,&M);
    fprintf(g,"%lld",gcd(N,M));
    fclose(f);
    fclose(g);
    return 0;
}
