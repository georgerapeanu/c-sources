#include<fstream>
using namespace std;
ifstream f("strand.in");
ofstream g("strand.out");
int main()
{
    long n,i,j,gasit=0,sd=0,ss;
    f>>n;
    long v[n];
    for(i=0;i<n;i++)
        f>>v[i];
    for(i=0;i<n&&gasit==0;i++)
    {
        sd=0;ss=0;
        for(j=0;j<=i;j++)
        {
            sd+=v[j];
        }
        for(j=n-1;j>i;j--)
        {
            ss+=v[j];
        }
        if(ss==sd) gasit=1;
    }
    g<<i;
    f.close();g.close();
    return 0;
}
