#include <cstdio>
#include <algorithm>
using namespace std;
FILE *f=fopen("placa.in","r");
FILE *g=fopen("placa.out","w");
int V[100005],a,b,N,M,K,i,maxS[100005],maxD[100005],minlocal,minglobal=9999999,st,dr,mid,pc,lc,last;
int main()
{
    fscanf(f,"%d %d %d",&N,&M,&K);
    for(i=1;i<=M;i++)
    {
        fscanf(f,"%d %d",&a,&b);
        if(a==N)
            V[i]=N;
        else
            V[i]=a+b;
    }
    for(i=1;i<=M;i++)
    {
        maxS[i]=max(maxS[i-1],V[i]);
        maxD[M-i+1]=max(maxD[M-i+2],V[M-i+1]);
    }
    for(i=1;i<=M-K+1;i++)
    {
        minlocal=max(maxS[i-1],maxD[i+K]);
        if(minlocal<minglobal)
            minglobal=minlocal;
    }
    st=1;
    dr=M;
    last=-1;
    while(st<=dr)
    {
        mid=(st+dr)/2;
        if(maxS[mid]>minglobal)
        {
            last=mid;
            dr=mid-1;
        }
        else
            st=mid+1;
    }
    pc=last;
    st=1;
    dr=M;
    last=-1;
    while(st<=dr)
    {
        mid=(st+dr)/2;
        if(maxD[mid]>minglobal)
        {
            last=mid;
            st=mid+1;
        }
        else
            dr=mid-1;
    }
    lc=last;
    fprintf(g,"%d\n%d",minglobal,lc-pc+1);
    fclose(f);
    fclose(g);
    return 0;
}
