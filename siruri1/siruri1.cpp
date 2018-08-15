#include<fstream>
#include<algorithm>
using namespace std;
ifstream f("siruri1.in");
ofstream g("siruri1.out");
int n;
int main()
{
    f>>n;
    int x[n],y[n],i,j,d[n],mini=1;
    for(i=0;i<n;i++)
    {
        f>>x[i];
        d[i]=x[i];
    }
    sort(d,d+n);
    for(i=0;i<n;i++)
    {
        for(j=0;j<n;j++)
        {
            if(d[i]==x[j])
            {
                y[j]=mini;
                mini++;
            }
        }
    }
    for(i=0;i<n;i++)
    {
        g<<y[i]<<" ";
    }
    f.close();g.close();
    return 0;
}
