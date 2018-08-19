#include <bits/stdc++.h>
using namespace std;
int i,j,k,S;
int N,M[105][105];
int maxs=-10000005;
int V[105];
int main()
{
    cin.sync_with_stdio(false);
    cout.sync_with_stdio(false);
    cin>>N;
    for(i=1;i<=N;i++)
    {
        for(j=1;j<=N;j++)
            cin>>M[i][j];
    }
    for(i=1;i<=N;i++)
    {
        for(j=1;j<=N;j++)
            V[j]=0;
        for(j=i;j<=N;j++)
        {
            for(k=1;k<=N;k++)
                V[k]+=M[j][k];
            S=0;
            for(k=1;k<=N;k++)
            {
                if(S<0)
                    S=0;
                S+=V[k];
                if(S>maxs)
                    maxs=S;
            }
            if(S==0)
                for(k=1;k<=N;k++)
                    if(V[k]>maxs)
                        maxs=V[k];
        }
    }
    cout<<maxs;
    return 0;
}
