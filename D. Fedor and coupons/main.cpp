#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
#include <unordered_set>
#define x first.first
#define sens first.second
#define ind second
using namespace std;
int u=1000000005,N,K,st,dr,rez;
vector<pair<pair<int,int>,int> > V;
int nractiv;
unordered_set<int> S,r;
int main()
{
    cin>>N>>K;
    for(int i=1;i<=N;i++)
    {
        cin>>st>>dr;
        V.push_back(make_pair(make_pair(st,-1),i));
        V.push_back(make_pair(make_pair(dr,1),i));
        u=min(u,st);
    }
    sort(V.begin(),V.end());
    for(int i=0;i<2*N;i++)
    {
        if(nractiv>=K&&V[i].x-u+1>rez)
            {rez=V[i].x-u+1;r=S;}
        nractiv-=V[i].sens;
        if(V[i].sens==-1)
            S.insert(V[i].ind);
        else
            S.erase(V[i].ind);
        u=V[i].x;
    }
    if(!rez)
        {cout<<"0\n";for(int i=1;i<=K;i++)cout<<i<<" ";}
    else
    {
        cout<<rez<<"\n";
        for(auto it:r)
            cout<<it<<" ";
    }
    return 0;
}
