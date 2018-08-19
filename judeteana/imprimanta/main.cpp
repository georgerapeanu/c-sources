#include <fstream>
using namespace std;
ifstream f("imprimanta.in");
ofstream g("imprimanta.out");
long long n,k,nrminimace=16,nrmaxim,c,nrcifremaxim,nraceramase,nrace,i;
int main()
{
    f>>n>>k;
    f.close();
    while(n)
    {
        c=n%10;
        n=n/10;
        switch(c)
        {
        case 0:
        case 6:
        case 9: nrace=12;break;
        case 1: nrace=5;break;
        case 2:
        case 3:
        case 5: nrace=11;break;
        case 4: nrace=9;break;
        case 7: nrace=7;break;
        case 8: nrace=13;break;
        }
        if(nrace<nrminimace)
        {
            nrminimace=nrace;nrmaxim=c;
        }
        else
             if(nrace==nrminimace&&c>nrmaxim)
             nrmaxim=c;
    }
    g<<nrmaxim<<"\n";
    nrcifremaxim=k/5;nraceramase=k%5;
    switch(nraceramase)
    {
            case 0: g<<"11";break;
            case 1: g<<"7";
                   if(nrcifremaxim==3) {g<<"4";nrcifremaxim=0;}
                      else {g<<"77"; nrcifremaxim-=2;}
               break;
            case 2: g<<"71";break;
            case 3: g<<"8";break;
            case 4: g<<"77";break;
    }
    for(i=1;i<=nrcifremaxim-2;i++)
    g<<1;
    g.close();
    return 0;
}
