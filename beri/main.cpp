#include <cstdio>
#include <algorithm>
using namespace std;
FILE *f=fopen("beri.in","r");
FILE *g=fopen("beri.out","w");
int N,K;
long long Q,X,Y,Z,rez;
int V[1000005];
int main()
{
    fscanf(f,"%d %d",&N,&K);
    fscanf(f,"%lld %lld %lld %lld",&Q,&X,&Y,&Z);
    V[1]=Q;
    for(int i=2;i<=N;i++) V[i]=((V[i-1]*X+Y)%Z+K);
    nth_element(V+1,V+N-K+1,V+1+N);
    for(int i=N;i>N-K;i--)
        rez=rez+(V[i]-N+i);
    fprintf(g,"%lld",rez);
    fclose(f);
    fclose(g);
    return 0;
}
