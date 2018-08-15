#include <iostream>
#include <cmath>
#include <cstring>
#include <map>
using namespace std;
struct poz
{
    int x,y;
};
map<char,poz> M;
string C[3];
string a;
int dp[105][30][30];
int dist(int a,int b)
{
    char A,B;
    A=a+'A';
    B=b+'A';
    return abs(M[A].x-M[B].x)+abs(M[A].y-M[B].y);
}
int main()
{
    C[0]="QWERTYUIOP";
    C[1]="ASDFGHJKL";
    C[2]="ZXCVBNM";
    for(int i=0;i<3;i++)
        for(int j=0;j<C[i].size();j++)
            M[C[i][j]]={i,j};

    memset(dp,0x3f3f3f3f,sizeof(dp));
    dp[0]['F'-'A']['J'-'A']=0;
    cin>>a;
    for(int i=1;i<=a.size();i++)
    {
        for(int j=0;j<26;j++)
        {
            for(int k=0;k<26;k++)
            {
                if(j==k||j==a[i-1]-'A')continue;
                dp[i][j][a[i-1]-'A']=min(dp[i][j][a[i-1]-'A'],dp[i-1][j][k]+dist(k,a[i-1]-'A'));
                dp[i][a[i-1]-'A'][j]=min(dp[i][a[i-1]-'A'][j],dp[i-1][k][j]+dist(k,a[i-1]-'A'));
            }
        }
    }
    int rez=(1<<30);
    for(int i=0;i<26;i++)
        for(int j=0;j<26;j++)
            if(rez>dp[a.size()][i][j])
                rez=dp[a.size()][i][j];
    cout<<rez;
    return 0;
}
