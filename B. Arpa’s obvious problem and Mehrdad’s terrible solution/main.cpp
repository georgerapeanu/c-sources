#include <iostream>

using namespace std;
long long frecv[200001];
int N,x,val;
long long rez;
int main()
{
    cin>>N>>x;
    for(int i=1;i<=N;i++)
    {
        cin>>val;
        rez+=frecv[val];
        frecv[val^x]++;
    }
    cout<<rez;
    return 0;
}
