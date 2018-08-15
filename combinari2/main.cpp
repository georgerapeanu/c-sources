#include <iostream>
#include <algorithm>
#include <cstdio>
#define KMAX 18
using namespace std;
int N,K;

bool V[KMAX];
/*void afisare()
{
    for(int i=1;i<=K;i++)
        cout<<comb[i]<<" ";
    cout<<"\n";
}
void btr(int pas)
{
    if(pas>K)
        afisare();
    else
    {
        for(int i=comb[pas-1]+1;i<=N-K+pas;i++)
        {
            comb[pas]=i;
            btr(pas+1);
        }
    }
}*/
int main()
{
    freopen("combinari.in","r",stdin);
    freopen("combinari.out","w",stdout);
    cin>>N>>K;
    for(int i=K+1;i<=N;i++)
        V[i]=1;
    do
    {
        for(int i=1;i<=N;i++)
        {
            if(V[i]==0)
                cout<<i<<" ";
        }
        cout<<"\n";
    }
    while(next_permutation(V+1,V+1+N));
    return 0;
}
