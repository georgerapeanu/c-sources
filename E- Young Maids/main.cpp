#include<iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;
int N;
bool U[200005];
int V[200005];
int lg2[200005];
priority_queue<pair<int,pair<int,int> >,vector<pair<int,pair<int,int> > >,greater<pair<int,pair<int,int> > > > H;
int RMQ[20][200005][2];
int getmin(int st,int dr,int p)
{
    if(dr<st)return 0;
    p=p^(!(st%2));
    int lg=lg2[dr-st+1];
    return (V[RMQ[lg][dr][p]]<V[RMQ[lg][st+(1<<lg)-1][p]] ? RMQ[lg][dr][p]:RMQ[lg][st+(1<<lg)-1][p]);
}
int main()
{
    lg2[0]=-1;
    cin>>N;
    for(int i=1;i<=N;i++)
    {
        cin>>V[i];
        RMQ[0][i][i%2]=i;
        lg2[i]=1+lg2[i/2];
    }
    V[0]=1<<30;
    for(int k=1;k<20;k++)
    {
        for(int i=(1<<k);i<=N;i++)
        {
            RMQ[k][i][0]=(V[RMQ[k-1][i][0]]<V[RMQ[k-1][i-(1<<(k-1))][0]] ? RMQ[k-1][i][0]:RMQ[k-1][i-(1<<(k-1))][0]);
            RMQ[k][i][1]=(V[RMQ[k-1][i][1]]<V[RMQ[k-1][i-(1<<(k-1))][1]] ? RMQ[k-1][i][1]:RMQ[k-1][i-(1<<(k-1))][1]);
        }
    }
    H.push({V[getmin(1,N,1)],{1,N}});
    while(!H.empty())
    {
        pair<int,int> tmp=H.top().second;H.pop();
        if(tmp.first>=tmp.second)continue;
        int x=getmin(tmp.first,tmp.second,1);
        int y=getmin(x+1,tmp.second,1);
        H.push({V[getmin(tmp.first,x-1,1)],{tmp.first,x-1}});
        //H.push({V[getmin(x+1,y-1,1)],{x+1,y-1}});
        //H.push({V[getmin(y+1,tmp.second,1)],{y+1,tmp.second}});
        //cout<<V[x]<<" "<<V[y]<<" ";
    }
    return 0;
}
