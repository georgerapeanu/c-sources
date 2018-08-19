#include <cstdio>
#include <set>
#include <vector>
#define x first
#define t second
#define pb push_back
#define mp make_pair
#define NMAX 200000
#define LL long long
#define zeros(i) (i&(-i))
using namespace std;
FILE *f=fopen("hapsan.in","r");
FILE *g=fopen("hapsan.out","w");
int N,M;
int S[NMAX+5];
int V[NMAX+5];
int A;
int B;
LL dp[NMAX+5];
LL maxdp[NMAX+5];
LL AIB[NMAX+5];
int u;
vector<pair<int,int> > Ev[NMAX+5];
multiset<int> H;
multiset<int>::iterator loc;
void update(int poz,LL val)
{
    for(int i=poz;i<=N;i+=zeros(i))
        AIB[i]=max(AIB[i],val);
}
LL query(int l,int r)
{
    LL rez=0;
    while(l<=r)
    {
        if(r-zeros(r)+1>=l) rez=max(rez,AIB[r]),r-=zeros(r);
        else rez=max(rez,dp[r]),r--;
    }
    return rez;
}
void computetill(int pas)
{
    for(int i=u+1;i<=pas;i++)
        update(S[i],dp[i]);
    u=pas;
}
int main()
{
    fscanf(f,"%d",&N);
    for(int i=1;i<=N;i++)
        fscanf(f,"%d",&S[i]);
    fscanf(f,"%d",&M);
    for(int i=1;i<=M;i++)
    {
        fscanf(f,"%d %d",&A,&B);
        Ev[A].pb(mp(A,1));
        Ev[B+1].pb(mp(A,-1));
    }
    for(int i=1;i<=N;i++)
    {
        for(auto it:Ev[i])
        {
            if(it.t==1)
            {
                H.insert(it.x);
            }
            else
            {
                loc=H.find(it.x);
                H.erase(loc);
            }
        }
        V[i]=*H.begin()-1;
    }
    LL rez=0;
    for(int i=1;i<=N;i++)
    {
        computetill(V[i]);
        dp[i]=query(1,S[i]-1)+S[i];
        rez=max(rez,dp[i]);
    }
    fprintf(g,"%lld",rez);
    fclose(f);
    fclose(g);
    return 0;
}
