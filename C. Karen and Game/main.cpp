#include <iostream>
#include <vector>
using namespace std;
int N,M,A[105][105];
vector<string> V;
string tmp;
string tost(int a)
{
    if(!a)return "";
    return tost(a/10)+(char)('0'+a%10);
}
void lin()
{
    for(int i=1;i<=N;i++)
    {
        int mini=1<<30;
        for(int j=1;j<=M;j++)mini=min(mini,A[i][j]);
        for(int j=1;j<=M;j++)A[i][j]-=mini;
        tmp="row "+tost(i);
        while(mini--)V.push_back(tmp);
    }
}
void col()
{
    for(int i=1;i<=M;i++)
    {
        int mini=1<<30;
        for(int j=1;j<=N;j++)mini=min(mini,A[j][i]);
        for(int j=1;j<=N;j++)A[j][i]-=mini;
        tmp="col "+tost(i);
        while(mini--)V.push_back(tmp);
    }
}
int main()
{
    cin>>N>>M;
    for(int i=1;i<=N;i++)for(int j=1;j<=M;j++)cin>>A[i][j];
    if(N>M){col();lin();}
    else {lin();col();}
    for(int i=1;i<=N;i++)for(int j=1;j<=M;j++)if(A[i][j]>0){cout<<-1;return 0;}
    cout<<V.size()<<"\n";
    for(auto it:V)cout<<it<<"\n";
    return 0;
}
