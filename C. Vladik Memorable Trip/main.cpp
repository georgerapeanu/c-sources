#include <iostream>
#include <bitset>
using namespace std;
int dp[5005];
int V[5005];
int X[5005];
int fstpos[5005];
int lastpos[5005];
int N;
int nrnotok;
int xo;
bitset<5005> notok;
bitset<5005> u;
int main()
{
    cin>>N;
    for(int i=1;i<=N;i++)
    {
        cin>>V[i];
        if(!fstpos[V[i]])fstpos[V[i]]=i;
        lastpos[V[i]]=i;
    }
    for(int i=1;i<=N;i++)
    {
        if(lastpos[V[i]]>i){dp[i]=dp[i-1];continue;}
        notok.reset();
        u.reset();
        nrnotok=0;
        dp[i]=dp[i-1];
        bool notc=0;
        xo=0;
        for(int j=i;j;j--)
        {
            if(lastpos[V[j]]>i)notc=1;
            if(notok[V[j]]&&fstpos[V[j]]==j&&!notc){nrnotok--;notok[V[j]]=0;}
            else if(!notok[V[j]]&&fstpos[V[j]]!=j&&!notc){nrnotok++;notok[V[j]]=1;}
            if(!u[V[j]]&&notc==0){u[V[j]]=1;xo^=V[j];}
            if(nrnotok==0)dp[i]=max(dp[j-1]+xo,dp[i]);
        }
    }
    cout<<dp[N];
    return 0;
}
