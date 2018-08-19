#include <fstream>
using namespace std;
ifstream f("imprimanta.in");
ofstream g("imprimanta.out");
int main()
{
 long long N,K;
 int c,minim_ace=15,cifra_maxima=0,nrace,nr_maxim_de_cifre, puncte_ramase,i;
 f>>N>>K;
 f.close();
 while(N)
 {
    c=N%10;
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
    if(nrace<minim_ace)
    {
         minim_ace=nrace;
         cifra_maxima=c;
    }
    else
       if(nrace==minim_ace && c>cifra_maxima)
            cifra_maxima=c;
    N=N/10;
 }
g<<cifra_maxima<<'\n';
nr_maxim_de_cifre=K/5; puncte_ramase=K%5;
 switch(puncte_ramase)
{
    case 0: g<<"11";break;
    case 1: g<<'7';
            if(nr_maxim_de_cifre==3) {g<<'4';nr_maxim_de_cifre=0;}
               else {g<<"77"; nr_maxim_de_cifre-=2;}
            break;
    case 2: g<<"71";break;
    case 3: g<<'8';break;
    case 4: g<<"77";break;
}
for(i=1;i<=nr_maxim_de_cifre-2;i++)
         g<<'1';
g<<'\n';
return 0;
}
