#include <fstream>
using namespace std;
ifstream f("submdisj.in");
ofstream g("submdisj.out");
int n,i,j,ultim,m[110][110];
int main()
{
    f>>n;
    if(n%2==0)
    {
    ultim=n*n;
        for(i=1;i<=n;i++)
        {
            for(j=1;j<=n/2;j++)
            {
                g<<ultim<<" "<<n*n+1-ultim<<" ";
                ultim--;
            }
            g<<"\n";
        }
    }
    else
    {
        i=1;
        j=n/2+1;
        ultim=2;
        m[i][j]=1;
        while(ultim<=n*n)
        {
            if(i==1)
            {
                if(j>=2&&m[n][j-1]==0)
                {
                    i=n;
                    j--;
                }
                else if(j==1&&m[n][j]==0)
                {
                    i=n;
                }
                else
                {
                    i++;
                }
            }
            else if(j==1)
            {
                if(i>=2&&m[i-1][n]==0)
                {
                    i--;
                    j=n;
                }
                else if(i==1&&m[i][n]==0)
                j=n;
                else
                i++;
            }
            else
            {
                if(m[i-1][j-1]==0)
                {
                    i--;
                    j--;
                }
                else
                i++;
            }
            m[i][j]=ultim;
            ultim++;
        }
    for(i=1;i<=n;i++)
        {
            for(j=1;j<=n;j++)
            {
                g<<m[i][j]<<" ";
            }
            g<<"\n";
        }
    }
    return 0;
}
