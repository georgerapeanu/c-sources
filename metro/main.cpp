#include <iostream>
#define inf 2000000
#include <cmath>
using namespace std;
int N,M;
double D[1001][1001];
int K,a,b;
bool P[1001][1001];
int main()
{
    cin>>N>>M>>K;
    while(K)
    {
        cin>>a>>b;
        P[a][b]=1;
        K--;
    }
    for(int i=0;i<=N;i++)
    {
        for(int j=0;j<=M;j++)
        {
            if(i||j)
                D[i][j]=inf;
            if(i!=0)
                D[i][j]=min(D[i][j],D[i-1][j]+100);
            if(j!=0)
                D[i][j]=min(D[i][j],D[i][j-1]+100);
            if(P[i][j])
                D[i][j]=min(D[i][j],sqrt(2)*100+D[i-1][j-1]);
        }
    }
    cout<<round(D[N][M]);
    return 0;
}
