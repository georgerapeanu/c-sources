#include<iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <set>
#include <bitset>
using namespace std;
int N;
int x;
set<int> S;
vector<int> G[205];
int L[205];
int R[205];
vector<int> Me,Mo;
bitset<205> U;
bool prime(int nr)
{
    if(nr<=2)return 0;
    for(int i=2;i*i<=nr;i++)if(nr%i==0)return 0;
    return 1;
}
bool pairup(int nod)
{
    if(U[nod])return 0;
    U[nod]=1;
    for(auto it:G[nod])
    {
        if(!R[it])
        {
            L[nod]=it;
            R[it]=nod;
            return 1;
        }
    }
    for(auto it:G[nod])
    {
        if(pairup(R[it]))
        {
            L[nod]=it;
            R[it]=nod;
            return 1;
        }
    }
    return 0;
}
int main()
{
    cin>>N;
    for(int i=1;i<=N;i++)
    {
        cin>>x;
        if(S.find(x)!=S.end())
        {
            S.erase(x);
        }
        else
        {
            S.insert(x);
        }
        S.insert(x+1);
    }
    for(auto it:S)
        if(it%2==0)
            Me.push_back(it);
        else
            Mo.push_back(it);
    for(int i=0;i<Me.size();i++)
    {
        for(int j=0;j<Mo.size();j++)
        {
            if(prime(abs(Mo[j]-Me[i])))
                G[i+1].push_back(j+1);
        }
    }
    bool ok=1;
    int k=0;
    while(ok)
    {
        ok=0;
        U.reset();
        for(int i=0;i<Me.size();i++)
        {
            if(!L[i+1]&&pairup(i+1))
            {
                k++;
                ok=1;
            }
        }
    }
    int rez=k+(((int)Me.size()-k)/2)*2+(((int)Mo.size()-k)/2)*2+(((int)Me.size()-k)%2)*3;
    cout<<rez;
    return 0;
}
