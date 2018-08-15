#include <fstream>
#include <cstring>
using namespace std;
ifstream f("opmult.in");
ofstream g("opmult.out");
char c;
int t,nr,i,j,l,k,nr1,nr2,op,maximnr,semn,nr1f,nr2f;
bool deschissf,deschisst,v[256],minimnr;
void citire()
{
     c=f.get();
        if(c=='(')
           deschisst=1;
        c=f.get();
        while(c<='9'&&c>='0')
        {
            nr1=nr1*10+c-'0';
            c=f.get();
        }
        c=f.get();
        while(c<='9'&&c>='0')
        {
            nr2=nr2*10+c-'0';
            c=f.get();
        }
        if(c==')')
        deschissf=1;
        if(deschissf!=0)
        nr2--;
        if(deschisst!=0)
        nr1++;

    if(nr1<minimnr)
    minimnr=nr1;
    if(nr2>maximnr)
    maximnr=nr2;
    deschissf=deschisst=0;
}
void umplere(int i1, int j1, int val)
{
    int i2;
    for(i2=i1;i2<=j1;i2++)
    v[i2]=val;
}
int main()
{
    f>>t;c=f.get();
    for(i=1;i<=t;i++)
    {
        c=f.get();maximnr=0;deschissf=deschisst=0;minimnr=255;nr=0;
        while(c<='9'&&c>='0')
        {
            nr=nr*10+c-'0';c=f.get();
        }
        citire();
        umplere(nr1,nr2,1);
        while(c!='\n')
        {
            c=f.get();nr1f=nr1;nr2f=nr2;nr1=nr2=0;
          switch(c)
          {
              case 'u':semn=0;
              break;
              case 'n':semn=1;
              break;
              case '-':semn=2;
              break;
              case '\n':semn=-1;
              break;
          }
          if(semn!=-1)
          {
          citire();
          if(semn==0)
          umplere(nr1,nr2,1);
          if(semn==2)
          {
              umplere(nr1,nr2,0);
          }
          if(semn==1)
          {
              umplere(nr1f,nr1-1,0);
              umplere(nr2f+1,nr2,0);
          }
        }
        }
        if(v[nr]==true)
        g<<"DA\n";
        else
        g<<"NU\n";
        umplere(minimnr,maximnr,0);
    }
    f.close();g.close();
    return 0;
}
