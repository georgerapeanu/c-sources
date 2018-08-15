#include <iostream>
using namespace std;
unsigned long long A[100005];
unsigned long long B[100005];
int N,i,l,rez;
bool ok;
int main()
{
    cin.sync_with_stdio(false);
    cout.sync_with_stdio(false);
    cin>>N;
    for(i=1;i<=N;i++)
    {
        cin>>A[i];
        A[i]=A[i-1]+A[i];
    }
    for(i=1;i<=N;i++)
    {
        cin>>B[i];
        B[i]=B[i-1]+B[i];
    }
    for(l=N;l>0&&!ok;l--)
    {
        for(i=1;i<=N-l+1&&!ok;i++)
        {
            if(A[i+l-1]-A[i-1]==B[i+l-1]-B[i-1])
                {ok=1;rez=l;}
        }
    }
    cout<<rez;
    return 0;
}
