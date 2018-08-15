#include <iostream>
using namespace std;
int i,N,R;
void a(int k)
{
    cout<<(k-1)*(k-2)*(k-3)*k/24;
    if(k==4) return ;
    cout<<"*";
    a(k-4);
}
int main()
{
    cin.sync_with_stdio(false);
    cout.sync_with_stdio(false);
    cin>>N>>R;
    cout<<"((";
    a(N);
    cout<<")";
    for(i=2;i<=N/4;i++)
        cout<<"/"<<i;
    cout<<")^"<<R;
    return 0;
}
