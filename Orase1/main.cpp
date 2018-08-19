#include <cstdio>
using namespace std;
FILE *f=fopen("orase1.in","r");
FILE *g=fopen("orase1.out","w");
int N,BK,K;
int D[1000005];
int cauta(int st,int dist)
{
    K--;
    int d=0;
    while(st<=N+1&&d<=dist)
    {
        d+=D[st];
        st++;
    }
    d=0;
    while(st<=N+1&&d<=dist)
    {
        d+=D[st-1];
        st++;
    }
    return st-1;
}
int ok(int dist)
{
    int i=1;
    while(K>=0&&i<=N)
    {
        i=cauta(i,dist);
    }
    if(K<0)
        return -1;
    return BK-K;
}
int main()
{
    fscanf(f,"%d %d",&N,&K);
    BK=K;
    for(int i=1;i<N;i++)
    {
        fscanf(f,"%d",&D[i]);
    }
    int st=1,dr=2000000,mid;
    while(st<dr)
    {
        mid=(st+dr)/2;
        K=BK;
        if(ok(mid)>=0)
        {
            dr=mid;
        }
        else
            st=mid+1;
    }
    K=BK;
    fprintf(g,"%d %d",st,ok(st));
    fclose(f);
    fclose(g);
    return 0;
}
