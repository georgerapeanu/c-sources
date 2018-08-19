#include <iostream>
#include <cmath>
using namespace std;
long long S[200005],rez=1LL<<62;
int N;
int main()
{
    cin>>N;
    for(int i=1;i<=N;i++)
    {
        cin>>S[i];
        S[i]+=S[i-1];
    }
    for(int i=1;i<N;i++)rez=min(rez,(long long)abs(S[i]-(S[N]-S[i])));
    cout<<rez;
    return 0;
}
