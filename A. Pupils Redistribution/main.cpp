#include <iostream>
#include <cmath>
using namespace std;
int A[6],B[6];
int a,b;
int N;
int delta;
int main()
{
    cin>>N;
    for(int i=1;i<=N;i++)
    {
        cin>>a;
        A[a]++;
    }
    for(int i=1;i<=N;i++)
    {
        cin>>b;
        B[b]++;
    }
    for(int i=1;i<=5;i++)
    {
        delta+=abs(A[i]-B[i]);
    }
    if(delta%4==0&&(A[0]+B[0])%2==0&&(A[1]+B[1])%2==0&&(A[2]+B[2])%2==0&&(A[3]+B[3])%2==0&&(A[4]+B[4])%2==0&&(A[5]+B[5])%2==0)
        cout<<delta/4;
    else cout<<-1;
    return 0;
}
