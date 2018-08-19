#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
using namespace std;
int N,M,K,l,r,a,col,maxim=-1,nr;
int F[100005][20];
int main() {
    freopen("in","r",stdin);
    freopen("out","w",stdout);
    cin>>N>>M;
    for(int i=1;i<=N;i++)
    {
        cin>>l>>r>>a;
        if(a==0){continue;}
        F[l][a]++;
        F[r+1][a]--;
        F[l][0]--;
        F[r+1][0]++;
    }
    for(int i=1;i<=M;i++)F[i]+=F[i-1];
    for(int i=1;i<=M;i++)
    {
        nr=0;
        for(int j=1;j<=10;j++)
        {
            F[i][j]+=F[i-1][j];
            if(F[i][j]>0)nr++;
        }
        F[i][0]+=F[i-1][0];
        if(F[i][0]>(-N))nr++;
        maxim=max(maxim,nr);
    }
    cout<<maxim;
    return 0;
}
