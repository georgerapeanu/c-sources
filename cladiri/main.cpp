#include <fstream>
#include <iostream>
using namespace std;
ifstream f("cladiri.in");
ofstream g("cladiri.out");
long long palindrom,nrc,n,j,v,i,cv,nrmax,maxi,uc,pc,p10c=1,nrad,gasit,dif,fi;
int main()
{
    f>>n;
    for(i=1;i<=n;i++)
    {
        f>>v;
        cv=v;
        p10c=1;nrc=0;fi=0;
        while(cv!=0)
        {
            uc=cv%10;
            cv=cv/10;nrc++;
            p10c=p10c*10;
            if(uc==maxi&&fi!=i)
            {
                nrmax++;fi=i;
            }
            if(uc>maxi)
            {
                maxi=uc;
                nrmax=1;fi=i;
            }
        }

        cv=v;
        p10c=p10c/10;gasit=1;
        for( j=1;j<=nrc/2;j++)
        {
            pc=cv/p10c;
            uc=cv%10;
            cv=cv%p10c;
            cv=cv/10;
            p10c=p10c/100;
            if(pc!=uc)
            {
                gasit=0;
                dif=pc-uc;
                if(dif<0)
                {
                    dif=dif*-1;
                }
                nrad=nrad+dif;
            }
        }
        if(gasit==1)
            palindrom++;
    }
    g<<maxi<<" "<<nrmax<<"\n"<<palindrom<<"\n"<<nrad;
    f.close();g.close();
    return 0;
}
