#include <iostream>
using namespace std;
int AIB[300005];
bool U[300005];
int N,poz;
void u(int pos,int val)
{
    for(;pos<=N;pos+=(-pos)&pos)AIB[pos]+=val;
}
int q(int pos)
{
    int sum=0;
    for(;pos;pos-=(-pos)&pos)sum+=AIB[pos];
    return sum;
}
int main()
{
    cin.sync_with_stdio(false);cin.tie(0);
    cout.sync_with_stdio(false);cout.tie(0);
    cin>>N;poz=N;
    cout<<"1 ";
    for(int i=1;i<=N;i++)
    {
        int s;
        cin>>s;
        U[s]=1;
        while(U[poz]&&poz>0)poz--;
        u(s+1,1);
        cout<<q(poz)+1<<" ";
    }
    return 0;
}
