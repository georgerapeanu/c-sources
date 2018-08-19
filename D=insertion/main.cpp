#include <iostream>
#include <cstdio>
#include <map>
#include <cstring>
#define INF 210
#define NMAX 105
using namespace std;
int dp[NMAX][NMAX];
string S[NMAX][NMAX],tmp;
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
        else if(K[i][j]==-1)
        {
            cout<<"(";
            afisare(i,j-1);
            cout<<")";
        }
        else if(K[i][j]==-2)
        {
            cout<<"(";
            afisare(i+1,j);
            cout<<")";
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
    cin>>N;
    cin.getline(C+1,105);
    cin.getline(C+1,105);
    M['(']=')';
    for(i=N;i>=1;i--)
    {
        for(j=i;j<=N;j++)
        {
            if(i==j)
                {dp[i][j]=1;S[i][j]="()";}
            else
            {
                dp[i][j]=INF;
                if(M[C[i]]==C[j])
                {
                    dp[i][j]=dp[i+1][j-1];
                    S[i][j]="("+S[i+1][j-1]+")";
                }
                if(C[j]==')')
                {
                    tmp="("+S[i][j-1]+")";
                    if(dp[i][j]>dp[i][j-1]+1||(dp[i][j]==dp[i][j-1]+1&&tmp<S[i][j]))
                    {
                        dp[i][j]=dp[i][j-1]+1;
                        S[i][j]=tmp;
                        K[i][j]=-1;
                    }
                }
                if(C[i]=='(')
                {
                    tmp="("+S[i+1][j]+")";
                    if(dp[i][j]>dp[i+1][j]+1||(dp[i][j]==dp[i+1][j]+1&&tmp<S[i][j]))
                    {
                        dp[i][j]=dp[i+1][j]+1;
                        S[i][j]=tmp;
                        K[i][j]=-2;
                    }
                }
                for(k=j;k>=i;k--)
                {
                    tmp=S[i][k]+S[k+1][j];
                    if(dp[i][j]>dp[i][k]+dp[k+1][j]||(dp[i][j]==dp[i][k]+dp[k+1][j]&&tmp<S[i][j]))
                    {
                        K[i][j]=k;
                        S[i][j]=tmp;
                        dp[i][j]=dp[i][k]+dp[k+1][j];
                    }
                }
            }
        }
    }

    cout<<S[1][N];
    return 0;
}
