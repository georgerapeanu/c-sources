#include <iostream>
#include <bitset>
#define NMAX 100005
using namespace std;
int f[NMAX];
int g[NMAX];
int h[NMAX];
int q[NMAX];
int p[NMAX];
bitset<NMAX> B;
int N;
int nr;
int main()
{
    cin>>N;
    for(int i=1;i<=N;i++)
    {
        cin>>f[i];
        if(!B[f[i]])
        {
            B[f[i]]=1;
            p[++nr]=f[i];
            q[f[i]]=nr;
        }
    }
    for(int i=1;i<=N;i++)
    {
        if(f[i]!=f[f[i]]){cout<<-1;return 0;}
        g[i]=q[f[i]];
    }
    cout<<nr<<"\n";
    for(int i=1;i<=N;i++)
        cout<<g[i]<<" ";
    cout<<'\n';
    for(int i=1;i<=nr;i++)
        cout<<p[i]<<" ";
    return 0;
}
