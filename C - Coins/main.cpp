#include <iostream>
#include <algorithm>
#include <queue>
using namespace std;
long long X[4];
long long Y[4];
long long ord[4];
long long N;
long long sum,rez;
long long U[100005];
long long V[100005][4];
void transfer(long long i,long long j)
{
    priority_queue<pair<long long,long long> > H;while(!H.empty())H.pop();
    for(long long k=1;k<=N;k++)
    {
        if(U[k]==i)
            H.push({V[k][j]-V[k][i],k});
    }
    while(!H.empty()&&Y[i]<0)
    {
        Y[i]++;Y[j]--;
        U[H.top().second]=j;
        sum+=H.top().first;
        H.pop();
    }
}
void transfer2(long long i,long long j)
{
    priority_queue<pair<long long,long long> > H;
    for(long long k=1;k<=N;k++)
    {
        if(U[k]==i)
            H.push({V[k][j]-V[k][i],k});
    }
    while(!H.empty()&&Y[i]<0&&Y[j]>0)
    {
        Y[i]++;Y[j]--;
        U[H.top().second]=j;
        sum+=H.top().first;
        H.pop();
    }
}
long long eval()
{
    Y[1]=X[1];
    Y[2]=X[2];
    Y[3]=X[3];
    sum=0;
    for(long long i=1;i<=N;i++)
    {
        sum+=V[i][ord[1]];
        Y[ord[1]]--;
        U[i]=ord[1];
    }
    transfer(ord[1],ord[2]);
    transfer(ord[2],ord[3]);
    return sum;
}
long long eval2()
{
    Y[1]=X[1];
    Y[2]=X[2];
    Y[3]=X[3];
    sum=0;
    for(long long i=1;i<=N;i++)
    {
        sum+=V[i][ord[1]];
        Y[ord[1]]--;
        U[i]=ord[1];
    }
    transfer2(ord[1],ord[2]);
    transfer2(ord[1],ord[3]);
    return sum;
}
int main()
{
    cin>>X[1]>>X[2]>>X[3];
    N=X[1]+X[2]+X[3];
    for(long long i=1;i<=N;i++)for(long long j=1;j<=3;j++)cin>>V[i][j];
    ord[1]=1;ord[2]=2;ord[3]=3;
    for(long long i=1;i<=6;i++)
    {
        rez=max(rez,eval());
        rez=max(rez,eval2());
        next_permutation(ord+1,ord+4);
    }
    cout<<rez;
    return 0;
}
