#include <iostream>

using namespace std;
void shl(int V[])
{
    for(int i=V[0]+1;i>2;i++)
        V[i]=V[i-1];
    V[1]=0;
    V[0]++;
}
void adunare()
{
    while(A[0]<B[0])shl(A);
    while(A[0]>B[0])shl(B);
    for(i=A[0];i>1;i--)
    {
        C[i]+=A[i]+B[i];
        C[i-1]+=C[i]/10;
        C[i]%=10;
    }
}
void resetare()
{
    for(int i=0;i<=B[0];i++)
        A[i]=B[i];
    for(int i=0;i<=C[0];i++)
        {B[i]=C[i];C[i]=0;}
}
int main()
{
    cout << "Hello world!" << endl;
    return 0;
}
