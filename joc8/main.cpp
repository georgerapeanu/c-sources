#include <iostream>
#include <cstdio>
#define inf 10000005
using namespace std;
int N,M,i,j,nr1,x,y,minim,pasi,S;
long long C[20][20];
char L[20][20];
int main()
{
    freopen("joc8.in","r",stdin);
    freopen("joc8.out","w",stdout);
    cin>>N>>M;
    for(i=1;i<=N;i++)
    {
        cin>>(L[i]+1);
        for(j=1;j<=M;j++)
            nr1+=(L[i][j]=='1');
    }
    for(i=1;i<=N;i++)
    {
        for(j=1;j<=M;j++)
        {
            C[i][j]=(1<<(N-i))+(1<<(M-j));
        }
    }
    while(nr1--)
    {
        minim=inf;
        x=y=0;
        for(i=1;i<=N;i++)
        {
            for(j=1;j<=M;j++)
            {
                if(minim>C[i][j])
                {
                    minim=C[i][j];
                    x=i;
                    y=j;
                }
                else if(minim==C[i][j]&&L[i][j]=='1')
                {
                    x=i;
                    y=j;
                }
            }
        }
        S+=C[x][y];
        pasi+=(L[x][y]=='0');
        C[x][y]=inf;
    }
    cout<<S<<" "<<pasi;
    return 0;
}
