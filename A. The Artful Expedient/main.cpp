#include <iostream>
using namespace std;
int fr[4000006];
int N;
int A[2005];
int B[2005];
int ans;
int main()
{
    cin>>N;
    for(int i=1;i<=N;i++)
    {
        cin>>A[i];
        fr[A[i]]++;
    }
    for(int i=1;i<=N;i++)
    {
        cin>>B[i];
        fr[B[i]]++;
    }
    for(int i=1;i<=N;i++)
    {
        for(int j=1;j<=N;j++)
        {
            ans+=(fr[A[i]^B[j]]!=0);
        }
    }
    cout<<(ans%2==0 ? "Karen":"Koyomi");
    return 0;
}
