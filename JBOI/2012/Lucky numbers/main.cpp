#include <iostream>
using namespace std;
int N;
string a;
int dp[255][5];
int main()
{
    cin>>N>>a;a=" "+a;
    for(int i=1;i<=N;i++)
    {
        dp[i][1]=(dp[i-1][1]+1)*(a[i]=='?'||a[i]=='2');
        dp[i][2]=(dp[i-1][2]+1)*(a[i]=='?'||a[i]=='3');
        dp[i][3]=(dp[i-1][3]+1)*(a[i]=='?'||a[i]=='5');
        dp[i][4]=(dp[i-1][4]+1)*(a[i]=='?'||a[i]=='7');
        if(dp[i][1]==2||dp[i][2]==3||dp[i][3]==5||dp[i][4]==7){cout<<"cool";return 0;}
    }
    cout<<"boring";
    return 0;
}
