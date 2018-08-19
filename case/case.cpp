#include<fstream>
using namespace std;
ifstream f("case.in");
ofstream g("case.out");
int n,i,v[10000],nra,nrmaxb,nrb,p,nrint[10000],nrcase[10000],c,d=0,e,nrc,mini=100000;
int main()
{
    f>>n;
    for(i=0;i<n;i++)
        f>>v[i];
    for(i=0;i<n;i++)
    {
        p=v[i];
        nrb=0;
        if((i+1)==v[i])
            nra++;
            while(i!=v[p])
            {
                p=v[p];
                e=c;
                if(d!=0&&d<=p)
                    c=1;
                if(d!=0&&d>=p)
                    c=2;
                d=p;
                if(e!=0&&e!=c)
                {
                    nrc++;
                }
                nrb++;
            }
            nrint[i]=nrc;
            if(mini<nrc)
                mini=nrc;
            if(nrb>nrmaxb)
                nrmaxb=nrb;
                nrcase[i]=nrb;
    }
   g<<nra<<"\n"<<nrmaxb<<"\n";
   for(i=0;i<n;i++)
   {
       if(nrcase[i]==nrmaxb)
       {
           if(nrint[i]==mini)
           {
               g<<(i+1);
               i=n;
           }
       }
   }
    f.close();g.close();
    return 0;
}
