#include <cstdio>
#include <algorithm>
#include <queue>
#define val first
#define fr second
using namespace std;
FILE *f=fopen("roboti3.in","r");
FILE *g=fopen("roboti3.out","w");
int N;
int t,ind;
int l,rez;
int V[200005];
int R[200005],dim;
int poz[2];
int dir[]={-1,1};
pair<int,int> A[200005];
queue<int> Q;
void solve1()
{
    if(Q.size()%2==0)
    {
        ind=1;
    }
    else
    {
        ind=0;
    }
    while(!Q.empty())
    {
        R[poz[ind]]=Q.front();
        poz[ind]+=dir[ind];
        ind^=1;
        Q.pop();
    }
}
void solve2(pair<int,int> a)
{
    R[poz[0]]=R[poz[1]]=a.val;
    poz[0]+=dir[0];
    poz[1]+=dir[1];
    a.fr-=2;
    while(a.fr)
    {
        R[poz[0]]=a.val;
        poz[0]+=dir[0];
        a.fr--;
    }
}
int main()
{
    fscanf(f,"%d",&t);
    fscanf(f,"%d",&N);
    for(int i=1;i<=N;i++)
    {
        fscanf(f,"%d",&V[i]);
    }
    if(t==1)
    {
        for(int i=N+1;i<=2*N;i++)
            V[i]=V[i-N];
        for(int i=1;i<=2*N;i++)
        {
            if(V[i-1]<V[i])
                l++;
            else
                l=1;
            rez=max(l,rez);
        }
        fprintf(g,"%d",rez);
    }
    else
    {
        sort(V+1,V+1+N);
        A[0].val=-1;
        dim=0;
        for(int i=1;i<=N;i++)
        {
            if(A[dim].val!=V[i])
                dim++;
            A[dim].val=V[i];
            A[dim].fr++;
        }
        poz[0]=N;
        poz[1]=1;
        for(int i=dim;i>1;i--)
        {
            if(A[i].fr==1)
            {
                Q.push(A[i].val);
            }
            else
            {
                solve1();
                solve2(A[i]);
            }
        }
        solve1();
        while(A[1].fr)
        {
            R[poz[0]]=A[1].val;
            poz[0]+=dir[0];
            A[1].fr--;
        }
        int pos=0;
        R[pos]=(1<<30);
        for(int i=1;i<=N;i++)
            if(R[i]<R[pos])
                pos=i;
        for(int i=pos;i<=N;i++)
            fprintf(g,"%d ",R[i]);
        for(int i=1;i<pos;i++)
            fprintf(g,"%d ",R[i]);
    }
    fclose(f);
    fclose(g);
    return 0;
}
