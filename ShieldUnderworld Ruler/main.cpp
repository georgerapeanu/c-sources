#include <cstdio>
#define x first
#define y second
using namespace std;
FILE *f=fopen("shield.in","r");
FILE *g=fopen("shield.out","w");
int N,L;
typedef pair<int,int> punct;
punct A[100005];
int N,tmax;
int poz=1;
int st;
multiset<int> S;
int gmin()
{
    return *S.begin();
}
int gmax()
{

    return *S.rbegin();
}
int main()
{
    fscanf(f,"%d%d",&N,&L);
    for(int i=1;i<=N;i++)
    {
        fscanf(f,"%d %d",&A[i].x,&A[i].y);
        tmax=max(A[i].x,tmax);
    }
    sort(A+1,A+1+N);
    st=1;
    for(int i=1;i<=tmax;i++)
    {
        S.erase(i);
        while(poz<=N&&A[poz].x<=i)
            poz++;
        while(poz<=N&&(S.empty()||gmax()-min(gmin())+1<=L))
    }
    return 0;
}
