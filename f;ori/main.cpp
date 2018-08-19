#include <fstream>
using namespace std;
ifstream f("flori1.in");
ofstream g("flori1.out");
int n,h,fl[101],s,a=1,sf,i,as,k=1,hold,j;
int main()
{
    f>>n>>h;
    sf=n*(n+1)/2;
    for(i=1;i<=n;i++)
    {
        f>>fl[i];sf+=fl[i];
    }
    s=(h-1)*n;i=0;
    while(a!=0)
    {
        for(i=1;i<=n;i++)
        {
            for(j=1;j<n;j++)
            {
                if(fl[j]>fl[j+1])
                {
                    hold=fl[j];fl[j]=fl[j+1];fl[j+1]=hold;
                }
            }
        }
        for(i=1;i<=k;i++)
        {
            fl[i]++;
            if(fl[i]==h)
               {
                   a=0;break;
               }
        }
        k++;
    }
    k--;
    g<<sf<<"\n"<<(k-1);
    f.close();g.close();
    return 0;
}
