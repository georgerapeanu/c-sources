#include <iostream>
using namespace std;
int W[2005];
int K[2005];
long long wmin[2005][2005];
long long T[2005][2005];
int N,Q;
int main()
{
    cin>>N>>Q;
    for(int i=0;i<N;i++)
        cin>>W[i];
    for(int i=0;i<N;i++)
        cin>>K[i];
    for(int i=N;i<2*N;i++)
    {
        W[i]=W[i-N];
        K[i]=K[i-N];
    }
    for(int i=2*N;i>=0;i--)
    {
        wmin[i][i]=T[i][i]=0;
        for(int j=i-1;j>=0&&j>i-N;j--)
        {
            wmin[j][i]=max(wmin[j+1][i]+K[j]-W[j],0LL);
            T[j][i]=T[j+1][i]+wmin[j+1][i]+K[j];
        }
    }
    while(Q--)
    {
        int x,y;
        cin>>x>>y;if(y<x)y+=N;
        if(wmin[x][y]>0)cout<<"-1\n";
        else cout<<T[x][y]<<"\n";
    }
    return 0;
}
