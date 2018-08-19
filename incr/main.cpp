#include <fstream>
#include <cmath>
using namespace std;
ifstream f("in.in");
ofstream g("out.out");
int a[100][100][100],i,j,k,nr,val,n;
int main()
{
    f>>n;
    nr=ceil(double(n)/2);
    for(i=1;i<=nr;i++)
    {
        val=1;
        for(j=1;j<=nr;j++)
        {
            for(k=j;k<=n-j+1;k++)
            {
                a[i][j][k]=a[i][k][j]=a[i][n-j+1][k]=a[i][k][n-j+1]=val;
                a[n-i+1][j][k]=a[n-i+1][k][j]=a[n-i+1][n-j+1][k]=a[n-i+1][k][n-j+1]=val;
            }
            if(val<i)
            val++;
        }
    }
    for(i=1;i<=n;i++)
    {
        for(j=1;j<=n;j++)
        {
            for(k=1;k<=n;k++)
            {
                 g<<a[i][j][k]<<" ";
            }
            g<<"\n";
        }
        g<<"\n\n";
    }
    f.close();g.close();
    return 0;
}
