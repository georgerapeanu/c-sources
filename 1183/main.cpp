#include <iostream>
#include <cstdio>
#include <map>
#include <cstring>
#define INF 210
#define NMAX 105
using namespace std;
int dp[NMAX][NMAX];
int K[NMAX][NMAX];
map<char,char> M;
int i,j,k,N;
char C[NMAX];
void afisare(int i,int j)
{
    if(i>j)
        return ;
    if(i==j)
    {
        if(C[i]=='('||C[i]==')')
            cout<<"()";
        else
            cout<<"[]";
    }
    else
    {
         if(K[i][j]==0&&M[C[i]]==C[j])
        {
            cout<<C[i];
            afisare(i+1,j-1);
            cout<<C[j];
        }
        else
        {
            afisare(i,K[i][j]);
            afisare(1+K[i][j],j);
        }
    }
}
int main()
{
    gets(C+1);
    M['(']=')';
    M['[']=']';
    N=strlen(C+1);
    for(i=N;i>=1;i--)
    {
        for(j=i;j<=N;j++)
        {
            if(i==j)
                dp[i][j]=1;
            else
            {
                dp[i][j]=INF;
                if(M[C[i]]==C[j])
                    dp[i][j]=dp[i+1][j-1];
                for(k=i;k<j;k++)
                    if(dp[i][j]>dp[i][k]+dp[k+1][j])
                    {
                        K[i][j]=k;
                        dp[i][j]=dp[i][k]+dp[k+1][j];
                    }
            }
        }
    }

    afisare(1,N);
    return 0;
}
