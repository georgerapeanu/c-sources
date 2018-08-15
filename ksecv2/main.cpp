#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <algorithm>
#define nmax 3000
#define sh short
using namespace std;
FILE *f=fopen("ksecv2.in","r");
FILE *g=fopen("ksecv2.out","w");
int A[505][4*nmax+5];
vector<int> norm;
int N,K;
int V[nmax+5];
void u(int k,int nod,int st,int dr,int poz,int val)
{
    if(st==dr){A[k][nod]=max(A[k][nod],val);return ;}
    int mid=(st+dr)/2;
    if(mid>=poz)u(k,2*nod,st,mid,poz,val);
    else u(k,2*nod+1,mid+1,dr,poz,val);
    A[k][nod]=max(A[k][2*nod],A[k][2*nod+1]);
}
int q(int k,int nod,int st,int dr,int c1,int c2)
{
    if(c2<st||c1>dr)return 0;
    if(c1<=st&&dr<=c2)return A[k][nod];
    int mid=(st+dr)/2;
    return max(q(k,nod*2,st,mid,c1,c2),q(k,nod*2+1,mid+1,dr,c1,c2));
}
int main()
{
    cout<<sizeof(A)/1000;
    fscanf(f,"%d %d",&N,&K);
    for(int i=1;i<=N;i++){fscanf(f,"%d",&V[i]);norm.push_back(V[i]);}
    sort(norm.begin(),norm.end());
    for(int i=1;i<=N;i++)
        V[i]=(lower_bound(norm.begin(),norm.end(),V[i])-norm.begin()+1);
    int m=-1;
    for(int i=1;i<=N;i++)
    {
        for(int j=1;j<=K;j++)
        {
            int act=max(q(j,1,1,N,1,V[i]),q(j-1,1,1,N,V[i]+1,N));
            if(act==0&&j!=1)continue;
            act++;
            if(j==K&&m<act)m=act;
            u(j,1,1,N,V[i],act);
        }
    }
    fprintf(g,"%d",m);
    fclose(f);
    fclose(g);
    return 0;
}
