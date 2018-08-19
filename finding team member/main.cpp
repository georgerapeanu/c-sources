#include <iostream>
using namespace std;
long long a[401][401],n,i,j,v[401],maxim,x,b[401][401],k;
bool used[401];
int main()
{
    cin>>n;
    for(i=1;i<=2*n-1;i++)
    {
        for(j=1;j<=i;j++)
        {
            cin>>a[i][j];
            x=1;
            while(b[i][x]<a[i][j]&&b[i][x]!=0)
            x++;
            for(k=b[i][0];k>=x+1;k--)
            {
                b[i][k]=b[i][k-1];
            }
            b[i][x]=j;
            b[i][0]++;
        }
    }
    for(i=1;i<=n;i++)
    {
        for(j=i;j>=1&&used[i]==0;j--)
        {
            if(b[b[i][j]][i]==i||used[b[i][j]]==0)
            {
                used[i]=1;
            }
        }
    }
    return 0;
}
