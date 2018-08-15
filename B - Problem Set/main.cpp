#include <iostream>
#include <map>
using namespace std;
map<int,int> A,T;
int N,M;
int main()
{
    cin.sync_with_stdio(false);cin.tie(0);
    cout.sync_with_stdio(false);cout.tie(0);
    cin>>N;
    for(int i=1;i<=N;i++)
    {
        int a;
        cin>>a;
        A[a]++;
    }
    cin>>M;
    for(int i=1;i<=M;i++)
    {
        int a;
        cin>>a;
        T[a]++;
        if(T[a]>A[a])
        {
            cout<<"NO";return 0;
        }
    }
    cout<<"YES";
    return 0;
}
