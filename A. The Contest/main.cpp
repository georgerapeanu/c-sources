#include <iostream>
using namespace std;
int N,M;
int val,l,r,s;
int main()
{
    cin.sync_with_stdio(false);
    cout.sync_with_stdio(false);
    cin>>N;
    for(int i=1;i<=N;i++)
    {
        cin>>val;
        s+=val;
    }
    cin>>M;
    for(int i=1;i<=M;i++)
    {
        cin>>l>>r;
        if(r>=s){cout<<max(s,l);return 0;}
    }
    cout<<-1;
    return 0;
}
