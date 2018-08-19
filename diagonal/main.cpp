#include <fstream>
#include <cstring>
using namespace std;
ifstream f("diagonal.in");
ofstream g("diagonal.out");
char m[100][100],c1[10000],c2[10000],nr;
long i,k,j,n;
int main()
{
    while(!f.eof())
    {
        f>>m[j];
        f.getline(m[j+1]+1,100);
        j++;
    }
    n=j-1;
    for(k=0;k<n;k++)
    {
        j=n-k-1;
        for(i=0;i<=k;i++)
        {
            c1[nr]=m[j][i];
            c2[nr]=m[i][n-j-1];
            nr++;j++;
        }
    }
    for(k=1;k<n;k++)
    {
        j=0;
        for(i=k;i<n;i++)
        {
            c1[nr]=m[j][i];
            c2[nr]=m[i][n-j-1];
            j++;
            nr++;
        }
    }
    g<<c1<<"\n"<<c2;
    return 0;
}
