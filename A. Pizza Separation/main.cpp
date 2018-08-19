#include <iostream>
#include <cmath>
#include <algorithm>
using namespace std;
int A[365];
int N;
int rez=4000;
int main()
{
    cin>>N;
    for(int i=1;i<=N;i++)
        cin>>A[i];
    for(int i=1;i<=N;i++)
    {
        int sum=0;
        for(int j=i;j<=N;j++)
        {
            sum+=A[j];
            rez=min((int)abs(360-2*sum),rez);
        }
    }
    cout<<rez;
    return 0;
}
