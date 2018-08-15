#include <iostream>
using namespace std;
bool I;
long long S;
int a;
int N;
int main()
{
    cin.sync_with_stdio(false);
    cout.sync_with_stdio(false);
    cin>>N;
    for(int i=1;i<=N;i++)
    {
        cin>>a;
        I|=(a&1);
        S+=a;
    }
    if(S%2==1||I)cout<<"First";
    else cout<<"Second";
    return 0;
}
