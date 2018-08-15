#include <iostream>
#include <bitset>
#include <unordered_set>
#define MOD 1000000007
using namespace std;
int N,M,P;
int V[105],nr;
unordered_set<int> S;
int btr(int pas)
{
    if(pas>P)
    {
        nr=(nr+(S.size()==N))%MOD;
        return;
    }
    for(int i=1;i<=N;i++)
    {
        int j;
        for(j=max(1,pas-M);j<pas&&V[j]!=i;j++);
        if(j==pas)
        {
            V[pas]=i;
            bool tmp=0;
            if(S.find(i)==S.end())
                tmp=1;
            S.insert(i);
            btr(pas+1);
            if(tmp)
                S.erase(i);
            V[pas]=0;
        }
    }
}
int main()
{
    cin>>N>>M>>P;
    btr(1);
    cout<<nr;
    return 0;
}
