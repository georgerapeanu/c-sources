#include <fstream>
using namespace std;
ifstream f("munte3.in");
ofstream g("munte3.out");
long long x[100],n,nrmunte,i,gasit,a,j;
int main()
{
    f>>n;
    gasit=1;
    for(i=0;i<n;i++)
    {
        f>>x[i];
    }
    while(gasit==1)
    {
        gasit=0;
        for(i=1;i<n-1;i++)
        {
            if(x[i]>x[i-1]&&x[i]>x[i+1])
            {
                for(j=i;j<n;j++)
                {
                        x[j]=x[j+1];gasit=1;
                }
                n--;nrmunte++;
            }
        }
        if(a==0)
        {
            g<<nrmunte<<"\n";
            a=1;
        }
    }
    g<<nrmunte<<"\n";
    g<<n;
    return 0;
}
