#include <fstream>
#include <cstring>
using namespace std;
ifstream f("grupe1.in");
ofstream g("grupe1.out");
int n,k,nr[201],nrf,nrb,gasit,i,j,a;
char c[200];
int main()
{
    f>>n>>k;
    f>>c;
    for(i=1;i<=k;i++)
    {
        nrb=0;
        nrf=0;
        f>>nr[i];
        for(j=1;j<=nr[i];j++)
        {
            f>>a;
            if(c[a-1]=='f')
                nrf++;
            else
                nrb++;
        }
        if((nrb-nrf>1)||(nrf-nrb>1))
            gasit=1;
       g<<nrb<<" "<<nrf<<"\n";
    }
    if(gasit==1)
        g<<"NU";
    else
    {
        for(i=1;i<=k;i++)
        {
            for(j=1;j<=k&&j!=i;j++)
            {
                if((nr[i]-nr[j]>1)||(nr[j]-nr[i]>1))
                {
                    gasit=1;
                    break;
                }
            }
        }
        if(gasit==1)
        g<<"NU";
        else
            g<<"DA";
    }
    f.close();g.close();
    return 0;
}
