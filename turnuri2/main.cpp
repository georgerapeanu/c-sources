#include <cstdio>
#include <algorithm>
#include <iostream>
#include <climits>
using namespace std;
FILE *f=fopen("turnuri2.in","r");
FILE *g=fopen("turnuri2.out","w");
typedef struct {int H,K;} date;
date V[1000005];
int st[1000005],dr[1000005],poz[1000005],i,j,N,maxim;
int main()
{
    fscanf(f,"%d",&N);
    for(i=1;i<=N;i++)
        fscanf(f,"%d %d",&V[i].H,&V[i].K);
    for(i=1;i<=N;i++)
    {
        maxim=V[i].K;
        for(j=i-1;j>0&&V[j].H<=V[i].H;j=poz[j])
        {
            if(st[j]>maxim)
                maxim=st[j];
        }
        if(V[j].K>maxim)
        maxim=V[j].K;
        poz[i]=j;
        st[i]=maxim;
    }
    for(i=N;i>=1;i--)
    {
        maxim=V[i].K;
        for(j=i+1;j<=N&&V[j].H<=V[i].H;j=poz[j])
        {
            if(dr[j]>maxim)
                maxim=dr[j];
        }
        if(V[j].K>maxim)
        maxim=V[j].K;
        poz[i]=j;
        dr[i]=maxim;
    }
    for(i=1;i<=N;i++)
        fprintf(g,"%d\n",max(dr[i],st[i]));
    fclose(f);
    fclose(g);
    return 0;
}
