#include <iostream>
#include <algorithm>
#include <vector>
#define inf 99999999
using namespace std;
int best[1005],i,D,N,M,X,a,b,j;
bool skipped[1005];
vector<int> V[1005];
int main()
{
    cin>>D>>N>>M;
    for(i=1;i<=N;i++)
    {
        cin>>X;
        skipped[X]=1;
    }
    for(i=1;i<=M;i++)
    {
        cin>>a>>b;
        V[a].push_back(b);
    }
    best[D+1]=0;
    for(i=D;i>0;i--)
    {
        best[i]=inf;
        if(skipped[i]==0)
            best[i]=best[i+1];
        else
        {
            N=V[i].size();
            for(j=0;j<N;j++)
            {
                best[i]=min(best[i],best[V[i][j]+1]+1);
            }
            if(N==0)
                best[i]=1;
        }
    }
    cout<<best[1];
    return 0;
}
