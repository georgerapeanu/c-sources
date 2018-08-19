#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
#define x first
#define y second
#define tip second
#define zeros(x) (x&(-x))
using namespace std;
int N,rez;
int V[100005];
int AIB[100005];
int q(int poz)
{
    int rez=0;
    for(;poz;poz-=zeros(poz))
        rez+=AIB[poz];
    return rez;
}
void u(int poz,int val)
{
    for(;poz<=N;poz+=zeros(poz))
        AIB[poz]+=val;
}
int main() {
    cin>>N;
    for(int i=1;i<=N;i++)cin>>V[i];
    for(int i=N;i;i--)
    {
        int mmari=q(N)-q(V[i]);
        rez=max(N-i+1-(mmari)+(mmari!=0),rez);
        u(V[i],1);
    }
    cout<<rez;
    return 0;
}
