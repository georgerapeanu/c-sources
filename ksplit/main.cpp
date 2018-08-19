#include <cstdio>
#include <cmath>
#define nmax 100005
using namespace std;
FILE *f=fopen("ksplit.in","r");
FILE *g=fopen("ksplit.out","w");
int drmax[nmax],stmax[nmax],drmin[nmax],stmin[nmax];
int pdrmax[nmax],pstmax[nmax],pdrmin[nmax],pstmin[nmax];
int V[nmax],N,d,l,dmax=-(1<<30),lmax;
int main()
{
    fscanf(f,"%d",&N);
    stmax[0]=-1;
    stmin[0]=1;
    for(int i=1;i<=N;i++)
    {
        fscanf(f,"%d",&V[i]);
        if(stmax[i-1]>=0) stmax[i]=stmax[i-1]+V[i],pstmax[i]=pstmax[i-1];
        else stmax[i]=V[i],pstmax[i]=i;
        if(stmin[i-1]<=0) stmin[i]=stmin[i-1]+V[i],pstmin[i]=pstmin[i-1];
        else stmin[i]=V[i],pstmin[i]=i;
    }
    drmax[N+1]=-1;
    drmin[N+1]=1;
    for(int i=N;i>=1;i--)
    {
        if(drmax[i+1]>=0) drmax[i]=drmax[i+1]+V[i],pdrmax[i]=pdrmax[i+1];
        else drmax[i]=V[i],pdrmax[i]=i;
        if(drmin[i+1]<=0) drmin[i]=drmin[i+1]+V[i],pdrmin[i]=pdrmin[i+1];
        else drmin[i]=V[i],pdrmin[i]=i;
    }
    for(int i=1;i<N;i++)
    {
        if(abs(drmax[i+1]-stmin[i])>abs(stmax[i]-drmin[i+1])) d=abs(drmax[i+1]-stmin[i]),l=pdrmax[i+1]-pstmin[i]+1;
        else d=abs(stmax[i]-drmin[i+1]),l=pdrmin[i+1]-pstmax[i]+1;
        if(d>dmax||(d==dmax&&l>lmax)) dmax=d,lmax=l;
    }
    fprintf(g,"%d\n%d",dmax,lmax);
    return 0;
}
