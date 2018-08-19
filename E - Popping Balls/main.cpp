#include <iostream>
#define MOD 1000000007
using namespace std;
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
int C[2005][2005];
int pr[2005][2005];
int mat[2005][2005];
int A,B;
int main()
{
    for(int i=0;i<=2000;i++)
    {
        C[i][0]=C[i][i]=1;
        for(int j=1;j<i;j++)
            C[i][j]=add(C[i-1][j],C[i-1][j-1]);
    }
    for(int i=0;i<=2000;i++)
        for(int j=0;j<=i;j++)
            pr[i][j]=add((j ? pr[i][j-1]:0),C[i][j]);
    for(int i=0;i<=2000;i++)mat[i][0]=mat[0][i]=1;
    for(int i=1;i<=2000;i++)
    {
        for(int j=1;j<=2000;j++)
        {
            mat[i][j]=add(mat[i][j-1],pr[j-1][min(j-1,i)]);
        }
    }
    cin>>A>>B;
    int ans=0;
    for(int i=0;i<=A;i++)
    {
        for(int j=0;j<=min(B-1,A-i);j++)
        {
            ans=add(ans,mult(C[B-1][j],mat[i][j]));
        }
    }
    cout<<ans;
    return 0;
}
