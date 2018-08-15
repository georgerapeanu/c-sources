#include <iostream>
using namespace std;
int F[8005];
string a;
int lg[8005];
int dp[8005];
int main()
{
    for(int i=1;i<=8000;i++){lg[i]=1+lg[i/10];dp[i]=1<<30;}
    cin>>a;
    a=" "+a;
    for(int i=1;i<a.size();i++)
    {
        F[1]=0;
        for(int j=i+1;j<a.size();j++)
        {
            int k=F[j-i];
            while(k&&a[j]!=a[i+k])k=F[k];
            if(a[k+i]==a[j])k++;
            F[j-i+1]=k;
        }
        for(int j=i;j<a.size();j++)
        {
            int per=j-i+1-F[j-i+1];
            if((j-i+1)%per!=0)per=j-i+1;
            dp[j]=min(dp[j],lg[(j-i+1)/per]+per+dp[i-1]);
        }
    }
    cout<<dp[a.size()-1];
    return 0;
}
