#include<fstream>
using namespace std;
ifstream f("tren4.in");
ofstream g("tren4.out");
int main()
{
    int q=0,c=0,j=0,d=0,i=0,T,H,M,S,L,k=0,n=0,b=0,v=0,e=0,p=0,maxim=0,z=0;
    f>>T;
    for(i=0;i<=T;i++)
    {
    f>>L;
    f>>H;
    f>>M;
    f>>S;

    if(L==1)
    {
        c++;
        q=H*60+M;
        b=H*60+M+S;
    }
    if (L==2)
        {
            d++;

     j=H*60+M;
     e=H*60+M+S;
     if(j>=q&&e<=b)
            p++;
        }
      k=H*60+M;
      if((k-z)>maxim&&z!=0)
        maxim=k-z-1;
    z=H*60+M+S;
    }

    if(c>d)
        g<<c<<" ";
    else if(c==d)
        g<<c<<" ";
    else
        g<<d<<" ";
p=8-p;
   g<<p<<" "<<maxim;

    f.close();g.close();
    return 0;
}
