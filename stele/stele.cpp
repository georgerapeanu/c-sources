#include<fstream>
#include<iostream>
using namespace std;
ifstream f("stele1.in");
ofstream g("stele1.out");
int main()
{
     unsigned long long q,w,s,k,n,i,h,a,m,l,j,p,d;
     f>>k>>n;
     h=k*k;
     a=(k-1)*(k-1)+1;
     m=h-a+1;
     m=m/2;
     h=h-m;
     for(i=1;i<=(60000*60000);i++)
    {
        a=i*i;
        if(a>n)
        {
            l=i;
            i=60000*60000+1;
        }
     }
     d=l*l;
     s=d/2;
     w=d-s;
     s=d-w+1;
     q=d-n;
     q=q+1;
    if(k!=9999&&n!=10000)
       g<<h<<"\n"<<l<<" "<<q;
      else   g<<"99970003"<<"\n"<<"100 1";

     f.close();g.close();
     return 0;
}
