#include <iostream>
using namespace std;
string a;
int dp[200005];
int bag[200005];
int nxt[200005][280];
bool cmp(string a,string b)
{
    if(a.empty())return 0;
    if(a.size()!=b.size())return a.size()<b.size();
    return a<=b;
}
int main()
{
    cin>>a;a=" "+a;
    for(int i='a';i<='z';i++)nxt[a.size()-1][i]=a.size();
    for(int i=a.size()-2;i>=0;i--){for(int c='a';c<='z';c++)nxt[i][c]=nxt[i+1][c];nxt[i][a[i+1]]=i+1;}
    for(int i=a.size()-1;i>=0;i--)
    {
        bag[i]=0;
        dp[i]=1<<30;
        for(int j='a';j<='z';j++)
            if(dp[i]>1+dp[nxt[i][j]])
                dp[i]=1+dp[nxt[i][j]],bag[i]=j;

    }
    int ind=0;
    while(ind!=a.size())
    {
        cout<<(char)bag[ind];
        ind=nxt[ind][bag[ind]];
    }
    return 0;
}
