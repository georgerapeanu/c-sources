#include <iostream>
#include <set>
#include <vector>
#define LIM 1000000000000000000LL
using namespace std;
vector<long long> VX;
vector<long long> VY;
vector<long long> V;
set<long long> S;
long long X,Y,l,r;
long long rez=0;
int main()
{
    cin>>X>>Y>>l>>r;
    long long bx=1;
    while(1)
    {
        VX.push_back(bx);
        if(LIM/X<bx)break;
        bx*=X;
    }
    long long by=1;
    while(1)
    {
        VY.push_back(by);
        if(LIM/Y<by)break;
        by*=Y;
    }
    for(auto a:VX)
    {
        for(auto b:VY)
        {
            if(a>LIM-b||a+b>r||a+b<l)continue;
            S.insert(a+b);
        }
    }
    V.push_back(l-1);
    for(auto it:S)V.push_back(it);
    V.push_back(r+1);
    for(int i=0;i<V.size()-1;i++)
        rez=max(rez,V[i+1]-V[i]-1);
    cout<<rez;
    return 0;
}
