#include <iostream>
using namespace std;
int N;
int L[1000005];
int last=1<<30,rez;
int main()
{
    cin.sync_with_stdio(false);cin.tie(0);
    cout.sync_with_stdio(false);cout.tie(0);
    cin>>N;
    for(int i=1;i<=N;i++)
        cin>>L[i];
    for(int i=N;i;i--)
    {
        if(i<last)rez++;
        last=min(last,i-L[i]);
    }
    cout<<rez;
    return 0;
}
