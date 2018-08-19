#include <cstdio>
#include <fstream>
#define inf 10000000005LL
using namespace std;
FILE *f=fopen("bursa.in","r");
FILE *g=fopen("bursa.out","w");
int N,i,st,dr,last,mid;
long long S,A,pmax,s,si;
int P[500005];
int main()
{
    fscanf(f,"%d %lld",&N,&S);
    for(i=1;i<=N;i++)
    {
        fscanf(f,"%d",&P[i]);
    }
    si=s=S;
    P[0]=inf;
    for(i=1;i<=N;i++)
    {
        if(P[i]<=P[i+1]&&P[i]<=P[i-1])
        {
            A+=S/P[i];
            S%=P[i];
        }
        else if(P[i]>P[i+1]&&P[i]>=P[i-1])
        {S+=A*P[i];A=0;}
    }
    fprintf(g,"%lld",S-si);
    fclose(f);
    fclose(g);
    return 0;
}
