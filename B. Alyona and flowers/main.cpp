#include <iostream>
using namespace std;
long long st,dr;
long long S[105];
long long N,M,rez;
int main()
{
    cin>>N>>M;
    for(long long i=1;i<=N;i++)
    {
        cin>>S[i];
        S[i]+=S[i-1];
    }
    for(long long i=1;i<=M;i++)
    {
        cin>>st>>dr;
        if(S[dr]-S[st-1]>0)
            rez+=S[dr]-S[st-1];
    }
    cout<<rez;
    return 0;
}
