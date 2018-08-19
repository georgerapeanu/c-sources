#include <cstdio>
#include <algorithm>
#include <cstring>
#define SIGMA 2
#define bit ((val&(1<<poz))!=0)
using namespace std;
FILE *f=fopen("xormax.in","r");
FILE *g=fopen("xormax.out","w");
int N;
int val,a,b,k,i;
int V[100005];
struct tn
{
    int cnt;
    int cine;
    tn *fiu[SIGMA];
    tn()
    {
        cnt=cine=0;
        memset(fiu,0,sizeof(fiu));
    }
};
tn *T;
void ins(tn *nod,int val,int poz)
{
    nod->cnt++;
    if(poz<0) {nod->cine=i;return ;}
    if(!nod->fiu[bit]) nod->fiu[bit]= new tn;
    ins(nod->fiu[bit],val,poz-1);
}
bool del(tn *nod,int val,int poz)
{
    nod->cnt--;
    if(poz<0);
    else if(del(nod->fiu[bit],val,poz-1))
    {
        nod->fiu[bit]=0;
    }
    if(!nod->cnt)
    {
        delete nod;
        return 1;
    }
    return 0;
}
int q(tn *nod,int val,int poz,int rez)
{
    if(poz<0) {k=nod->cine;return rez;}
    if(nod->fiu[!bit]!=0)
        return q(nod->fiu[!bit],val,poz-1,rez+(1<<poz));
    return q(nod->fiu[bit],val,poz-1,rez);
}
int main()
{
    fscanf(f,"%d",&N);
    T=new tn;
    ins(T,0,20);
    for(i=1;i<=N;i++)
    {
        fscanf(f,"%d",&V[i]);
    }
    val=0;
    int maxim=-1;
    for(i=1;i<=N;i++)
    {
        val^=V[i];
        int tmp=q(T,val,20,0);
        if(tmp>maxim)
        {
            maxim=tmp;
            a=k+1;
            b=i;
        }
        ins(T,val,20);
    }
    fprintf(g,"%d %d %d",maxim,a,b);
    fclose(f);
    fclose(g);
    return 0;
}
