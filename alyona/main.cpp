#include <iostream>
using namespace std;
int N,M;
long long A[10],B[10],R;
int main()
{
    cin>>N>>M;
    A[0]=N/5;
    A[1]=N/5+((N%5)>=1);
    A[2]=N/5+((N%5)>=2);
    A[3]=N/5+((N%5)>=3);
    A[4]=N/5+((N%5)>=4);
    B[0]=M/5;
    B[1]=M/5+((M%5)>=1);
    B[2]=M/5+((M%5)>=2);
    B[3]=M/5+((M%5)>=3);
    B[4]=M/5+((M%5)>=4);
    R=A[0]*B[0]+A[1]*B[4]+A[2]*B[3]+A[3]*B[2]+A[4]*B[1];
    cout<<R;
    return 0;
}
