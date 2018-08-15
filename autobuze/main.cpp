#include <cstdio>
#include <bitset>
#include <algorithm>
#define MOD 50000
using namespace std;
FILE *f=fopen("autobuze.in","r");
FILE *g=fopen("autobuze.out","w");
int N,i,nr,rez;
int mval;
int j;
int V[50001];
int P[50001];
vector<int> E[MOD+1];
bitset <10000005> B,Ex;
int fi(int x)
{
    if(P[x]<0)
        return x;
    P[x]=fi(P[x]);
    return P[x];
}
void u(int a,int b)
{
    a=fi(a);
    b=fi(b);
    if(a==b)
        return;
    if(P[a]<P[b]) {P[a]+=P[b];P[b]=a;}
    else {P[b]+=P[a];P[a]=b;}
}
int gaseste(int ind,int val)
{
    int st=0;
    int dr=E[ind].size()-1;
    if(dr<0)
        return 0;
    while(st<dr)
    {
        int mid=(st+dr)/2;
        if(V[E[ind][mid]]<val)
            st=mid+1;
        else
            dr=mid;
    }
    if(V[E[ind][st]]==val)
        return E[ind][st];
    return 0;
}
int main()
{
    fscanf(f,"%d",&N);
    nr=0;
    for(i=1;i<=N;i++)
    {
        fscanf(f,"%d",&V[i]);
        mval=max(mval,V[i]);
        Ex[V[i]]=1;
    }
    sort(V+1,V+1+N);
    for(int i=1;i<=N;i++)
    {
        E[V[i]%MOD].push_back(i);
        P[i]=-1;
    }
    rez=N;
    for(int i=1;i<=N;i++)
    {
        if(!B[V[i]])
        {
            bool nok=0;
            for(int j=V[i]+V[i];j<=mval;j+=V[i])
            {
                if(Ex[j])
                {
                    int val=gaseste(j%MOD,j);
                    u(i,val);
                    B[j]=1;
                }
            }
        }
    }
    for(int i=1;i<=N;i++) if(P[i]<0) nr++;
    fprintf(g,"%d",nr);
    fclose(f);
    fclose(g);
    return 0;
}
