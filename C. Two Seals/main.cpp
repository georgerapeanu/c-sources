#include <iostream>
using namespace std;
int N,A,B;
int X[205];
int Y[205];
int rez=0;
int main()
{
    cin>>N>>A>>B;
    for(int i=1;i<=N;i++)cin>>X[i]>>Y[i];
    for(int i=N+1;i<=2*N;i++){X[i]=Y[i-N];Y[i]=X[i-N];}
    N*=2;
    for(int i=1;i<=N;i++)
    {
        for(int j=1;j<=N;j++)
        {
            if(i==j||i==j-N/2||j==i-N/2)continue;
            if((X[i]+X[j]<=A&&Y[j]<=B&&Y[i]<=B)||(Y[i]+Y[j]<=B&&X[i]<=A&&X[j]<=A))
                rez=max(rez,X[i]*Y[i]+X[j]*Y[j]);
        }
    }
    cout<<rez;
    return 0;
}
