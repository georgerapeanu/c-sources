#include <cstdio>
#include <iostream>
#include <algorithm>
#define XMAX 260005
using namespace std;
FILE *f=fopen("1.out","r");
FILE *g=fopen("sea2.out","w");
struct nod{int x,y,poz;};
nod T[200005];
int sol[200005];
int AIB[XMAX];
int N;
bool cmp(nod a,nod b)
{
    return a.y>b.y;
}
int q(int poz)
{
    int rez=(1<<30);
    for(;poz<XMAX;poz+=poz&(-poz))
    {
        if(AIB[poz])
            rez=min(AIB[poz],rez);
    }
    if(rez!=(1<<30))
        return rez;
    return -1;
}
void upd(int poz,int ind)
{
    for(;poz;poz-=(-poz)&poz)
    {
        if(!AIB[poz])
            AIB[poz]=ind;
        else
            AIB[poz]=min(ind,AIB[poz]);
    }
}
int main()
{
    fscanf(f,"%d",&N);
    for(int i=1;i<=N;i++)
    {
        fscanf(f,"%d %d",&T[i].x,&T[i].y);
        T[i].poz=i;
    }
    sort(T+1,T+1+N,cmp);
    for(int i=1;i<=N;i++)
    {
        int val=q(T[i].x);
        if(val==-1||val>T[i].poz)
        {
            sol[val]++;
            upd(T[i].x,T[i].poz);
        }
        else
        {
            sol[T[i].poz]=-1;
        }
    }
    int nr=0;
    for(int i=1;i<=N;i++)
    {
        nr++;
        if(sol[i]==-1)
        {
            nr--;
            fprintf(g,"%d\n",sol[i]);
        }
        else
        {
            nr-=sol[i];
            fprintf(g,"%d\n",nr);
        }
    }
    fclose(f);
    fclose(g);
    return 0;
}
