#include <iostream>
using namespace std;
int rest[1001],i,j,n,m,dist;
bool uz[1001][1001],r[1001];
long nr;
int main()
{
    cin>>n>>m;
    for(i=1;i<=n;i++)
    {
        cin>>nr;
        rest[i]=nr%m;
        uz[nr%m][i]=1;
        r[nr%m]=1;
    }
    for(i=1;i<=m;i++)
    {
        for(j=1;j<=n;j++)
        {
            if(r[j]==1)
            {
                if()
            }
        }
    }
    return 0;
}
