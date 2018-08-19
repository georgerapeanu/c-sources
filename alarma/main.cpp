#include <fstream>
#include<stdlib.h>
using namespace std;
ifstream f("alarma.in");
ofstream g("alarma.out");
int ora,minut,cs1,cs2,cs3,cs4,c1,c2,c3,c4,calorii,minimal=10000,i,x[10],y[10],timp;
int main()
{
    for(i=0;i<=9;i++)
    {f>>x[i]>>y[i];}
    f>>timp;
    for(ora=timp/100;ora<100;ora+=24)
    {
        for(minut=timp%100;minut<100;minut+=60)
        {
            calorii=0;
            c1=ora/10;
            c2=ora%10;
            c3=minut/10;
            c4=minut%10;
            calorii=abs(x[c2]-x[c1])+abs(y[c2]-y[c1])+abs(x[c3]-x[c2])+abs(y[c3]-y[c2])+abs(x[c4]-x[c3])+abs(y[c4]-y[c3]);
            if(calorii<minimal)
            {minimal=calorii;cs1=c1;cs2=c2;cs3=c3;cs4=c4;}
        }
    }
    g<<minimal<<'\n'<<cs1<<cs2<<cs3<<cs4;
    g.close();f.close();
    return 0;
}
