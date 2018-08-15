#include <iostream>
using namespace std;
int A[100005];
int frecv[2000005];
int N;
int X;
long long rez;
int main()
{
    cin>>N;
    for(int i=1;i<=N;i++)
    {
        cin>>A[i];
        frecv[A[i]]++;
    }
    cin>>X;
    for(int i=1;i<=N;i++)
    {
        frecv[A[i]]--;
        if(A[i]>X)continue;
        rez+=frecv[X-A[i]];
    }
    cout<<rez;
    return 0;
}
