#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <set>
using namespace std;
multiset<int> S;
multiset<int> ::iterator it;
int N,Q;
int V[500005];
int gmax()
{
    if(S.empty())
        return 0;
    return *(S.rbegin());
}
int gmin()
{
    if(S.empty())
        return (1<<30);
    return *(S.begin());
}
long long q(long long val)
{
    int st,dr;
    long long rez=0;
    for(int st=1,dr=0;st<=N;st++)
    {
        dr=max(dr,st-1);
        while(1LL*max(gmax(),V[dr+1])-min(gmin(),V[dr+1])<=val&&dr<N)
        {
            dr++;
            S.insert(V[dr]);
        }
        rez=rez+(dr-st+1);
        it=S.find(V[st]);
        if(it!=S.end())
            S.erase(it);
    }
    return rez;
}
int main() {
    cin>>N>>Q;
    for(int i=1;i<=N;i++)
        cin>>V[i];
    for(int i=1;i<=Q;i++)
    {
        int a,b;
        cin>>a>>b;
        cout<<q(b)-q(a-1)<<"\n";
    }
    return 0;
}
