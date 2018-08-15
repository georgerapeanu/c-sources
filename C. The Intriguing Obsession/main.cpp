#include <iostream>
using namespace std;
int a,b,c;
int C[5005][5005];
int A[5005][5005];
const int MOD=998244353;
int add(int a,int b)
{
    a+=b;
    if(a>=MOD)a-=MOD;
    return a;
}
int mult(int a,int b)
{
    return 1LL*a*b%MOD;
}
int solve(int a,int b,int c)
{
    int rez1=0,rez2=0;
    for(int i=0;i<=a;i++)
    {
        rez1=add(rez1,mult(C[a][i],A[b][a-i]));
        rez2=add(rez2,mult(C[a][i],A[c][a-i]));
    }
    return mult(rez1,rez2);
}
int main()
{
    C[0][0]=1;
    for(int i=1;i<=5000;i++)
    {
        C[i][0]=C[i][i]=1;
        for(int j=1;j<i;j++)C[i][j]=add(C[i-1][j],C[i-1][j-1]);
    }
    A[0][0]=1;
    for(int i=1;i<=5000;i++)
    {
        A[i][0]=1;
        for(int j=1;j<i;j++)A[i][j]=mult(A[i-1][j-1],i);
        A[i][i]=A[i][i-1];
    }
    cin>>a>>b>>c;
    cout<<mult(solve(a,b,c),solve(b,0,c));
    return 0;
}
