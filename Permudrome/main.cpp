#include <iostream>
using namespace std;
int used[35][35][35],fr[35];
int dp[35][35],i,j,k;
char C[35],b,a;
bool inter[35][35];
int N,M;
int main()
{
    cin.getline(C+1,35);
    N=strlen(C+1);
    for(i=1;i<=N;i++)
        fr[C[i]-'a']++;
    cin>>M;
    for(i=1;i<=M;i++)
    {
        cin>>a>>b;
        inter[a-'a'][b-'a']=1;
        inter[b-'a'][a-'a']=1;
    }
    for(i=1;i<=N;i++)
    {
        for(j=1;j<=N;j++)
        {
            for(k=0;k<=25;k++)
            {
                if((!inter[j][k+'a'])&&fr[j-'a']-used[i-1][k]>0)
            }
        }
    }
    return 0;
}
