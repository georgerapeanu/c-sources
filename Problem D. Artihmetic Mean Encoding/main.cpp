#include <iostream>
#include <queue>
using namespace std;
priority_queue <int> H;
int T;
int nr1(long long n)
{
    int nr=0;
    while(n)
    {
        nr++;
        n-=(-n)&n;
    }
    return nr;
}
void scrie(long long n,int k)
{
    cout<<k<<" ";
    for(int i=0;i<63;i++)
        if((n>>i)&1)
            H.push(i);
    while(H.size()<k)
    {
        int nod=H.top()-1;
        H.pop();
        H.push(nod);
        H.push(nod);
    }
    while(!H.empty())
    {
        cout<<H.top()<<" ";
        H.pop();
    }
    cout<<"\n";
}
int main()
{
    cin>>T;
    while(T--)
    {
        long long nr;
        cin>>nr;
        int k=1;
        while(nr1(nr*k)>k)k++;
        scrie(nr*k,k);
    }
    return 0;
}
