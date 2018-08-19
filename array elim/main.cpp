#include <iostream>
#include <algorithm>
#include <map>
#include <vector>
using namespace std;
long long N;
long long AIB[100005];
map<long long,long long> S,D;
map<long long,vector<long long> > tmp;
long long dp[100005][2];
long long V[100005];
vector<long long> vals,T;
void u(long long pos,long long val)
{
    for(;pos<=N;pos+=(-pos)&pos)AIB[pos]+=val;
}
long long q(long long pos)
{
    long long sum=0;
    for(;pos;pos-=(-pos)&pos)sum+=AIB[pos];
    return sum;
}
long long dist(long long st,long long dr)
{
    if(st>dr)
        return q(st-1)-q(dr-1);
    return q(dr)-q(st);
}
long long computedist(long long ind,long long st,long long dr,long long val,bool capat)
{
    long long rez=0;
    if(!capat)
    {
        rez+=dist(ind,dr);
        for(auto it:tmp[val])
        {
            if(ind<=it&&it<=dr)u(it,-1);
        }
        rez+=dist(dr,st);
        for(auto it:tmp[val])
        {
            if(ind<=it&&it<=dr)u(it,1);
        }
    }
    else
    {
        rez+=dist(ind,st);
        for(auto it:tmp[val])
        {
            if(ind>=it&&st<=it)u(it,-1);
        }
        rez+=dist(st,dr);
        for(auto it:tmp[val])
        {
            if(ind>=it&&st<=it)u(it,1);
        }
    }
    return rez;
}
int main() {
    cin>>N;
    vals.push_back(-1);
    for(int i=1;i<=N;i++)
    {
        u(i,1);
        cin>>V[i];
        vals.push_back(V[i]);
        if(!S[V[i]])S[V[i]]=i;
        D[V[i]]=i;
        tmp[V[i]].push_back(i);
    }
    sort(vals.begin(),vals.end());
    T.push_back(-1);
    for(auto it:vals)
    {
        if(T.back()!=it)T.push_back(it);
    }
    vals.clear();for(auto it:T)vals.push_back(it);
    dp[1][0]=computedist(1,S[vals[1]],D[vals[1]],vals[1],0);
    dp[1][1]=computedist(1,S[vals[1]],D[vals[1]],vals[1],1);
    for(auto it:tmp[vals[1]])u(it,-1);
    for(int i=2;i<vals.size();i++)
    {
        dp[i][0]=min(dp[i-1][0]+computedist(S[vals[i-1]],S[vals[i]],D[vals[i]],vals[i],0),dp[i-1][1]+computedist(D[vals[i-1]],S[vals[i]],D[vals[i]],vals[i],0));
        dp[i][1]=min(dp[i-1][0]+computedist(S[vals[i-1]],S[vals[i]],D[vals[i]],vals[i],1),dp[i-1][1]+computedist(D[vals[i-1]],S[vals[i]],D[vals[i]],vals[i],1));
        for(auto it:tmp[vals[i]])u(it,-1);
    }
    cout<<min(dp[vals.size()-1][0],dp[vals.size()-1][1])+1;
    return 0;
}
