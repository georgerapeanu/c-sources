#include <cstring>
#include <cstdio>
#include <vector>
#define MOD 1000000007
using namespace std;
int A[100005];
int fr[100005];
vector<int> DIV[100005];
int N,Q,T;
void solve()
{
    memset(A,0,sizeof(A));
    memset(fr,0,sizeof(fr));
    scanf("%d %d",&N,&Q);
    for(int i=1;i<=N;i++)
    {
        scanf("%d",&A[i]);
        int tmp=(1LL*A[i]*A[i])%MOD;
        for(auto it:DIV[i])
        {
            fr[it]+=tmp;
            if(fr[it]>=MOD)fr[it]-=MOD;
        }
    }
    while(Q--)
    {
        int t,x,y;
        scanf("%d %d",&t,&x);
        if(t==1)
        {
            printf("%d\n",fr[x]);
        }
        else
        {
            scanf("%d",&y);
            int tmp=(-1LL*A[x]*A[x]+1LL*y*y)%MOD;
            if(tmp<0)tmp+=MOD;
            for(auto it:DIV[x])
            {
                fr[it]+=tmp;
                if(fr[it]>=MOD)fr[it]-=MOD;
            }
            A[x]=y;
        }
    }
}
void compute()
{
    for(int i=1;i<=100000;i++)
    {
        for(int j=i;j<=100000;j+=i)
        {
            DIV[j].push_back(i);
        }
    }
}
int main()
{
    compute();
    scanf("%d",&T);
    while(T--)solve();
    return 0;
}
