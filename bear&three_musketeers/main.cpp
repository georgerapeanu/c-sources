#include <iostream>
#define inf 1000000005
using namespace std;
bool m[4001][4001];
int i,j,k,n,m0,a[4001],nr,nrb,rez=inf;
int main()
{
    cin>>n>>m0;
    for(i=1;i<=m0;i++)
    {
        cin>>nr>>nrb;
        a[nr]++;
        a[nrb]++;
        m[nr][nrb]=m[nrb][nr]=1;
    }
    for(i=1;i<=n;i++)
    {
        for(j=i+1;j<=n;j++)
        {
            if(m[i][j]==1)
            {
                for(k=j+1;k<=n;k++)
                {
                    if(m[j][k]&&m[i][k])
                    rez=rez<a[i]+a[j]+a[k] ? rez:a[i]+a[j]+a[k];

                }
            }
        }
    }
    if(rez==inf)
    cout<<-1;
    else
    cout<<rez-6;
    return 0;
}
