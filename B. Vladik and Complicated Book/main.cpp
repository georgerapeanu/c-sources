#include <iostream>
using namespace std;
int N,M;
int V[10005];
int nr(int st,int dr,int val)
{
    int nr=0;
    for(int i=st;i<=dr;i++)nr+=(V[i]<val);
    return nr;
}
int main()
{
    cin.sync_with_stdio(false);
    cout.sync_with_stdio(false);
    cin>>N>>M;
    for(int i=1;i<=N;i++)cin>>V[i];
    for(int i=1;i<=M;i++)
    {
        int x,y,z;
        cin>>x>>y>>z;
        int val=V[z];
        if(z<x||z>y||x+nr(x,y,val)==z)cout<<"Yes\n";
        else cout<<"No\n";
    }
    return 0;
}
