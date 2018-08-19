#include <iostream>
using namespace std;
int A[5],N;
int main()
{
    cin>>N;
    A[1]=1;
    A[2]=1;
    A[3]=2;
    A[4]=4;
    if(N<=4)
        cout<<A[N];
    else
    {
        N-=4;
        while(N)
        {
            A[1]=A[2];
            A[2]=A[3];
            A[3]=A[4];
            A[4]=A[1]+A[3]+1;
            N--;
        }
        cout<<A[4];
    }
    return 0;
}
