#include <iostream>
#include <algorithm>
#include <map>
using namespace std;
pair<int,int> V[55];
map<int,int> X,Y;
int invX[55],invY[55];
int N,K;
long long rez=1LL<<62;
int S[55][55];
int main()
{
    cin>>N>>K;
    for(int i=1;i<=N;i++)
    {
        cin>>V[i].first>>V[i].second;
        X[V[i].first]=1;
        Y[V[i].second]=1;
    }
    int nr=0;
    for(auto &it:X)
    {
        it.second=++nr;
        invX[it.second]=it.first;
    }
    N=nr;
    nr=0;
    for(auto &it:Y)
    {
        it.second=++nr;
        invY[it.second]=it.first;
    }
    int M=nr;
    for(int i=1;i<=N;i++)
    {
        int x=X[V[i].first],y=Y[V[i].second];
        S[x][y]++;
    }
    for(int i=1;i<=N;i++)
    {
        for(int j=1;j<=M;j++)
        {
            S[i][j]+=S[i-1][j]+S[i][j-1]-S[i-1][j-1];
        }
    }
    for(int i=1;i<=N;i++)
    {
        for(int j=1;j<=M;j++)
        {
            for(int k=i;k<=N;k++)
            {
                for(int l=j;l<=M;l++)
                {
                    if(S[k][l]-S[k][j-1]-S[i-1][l]+S[i-1][j-1]>=K)
                    {
                        rez=min(rez,1LL*abs(invX[k]-invX[i])*abs(invY[l]-invY[j]));
                    }
                }
            }
        }
    }
    cout<<rez;
    return 0;
}
