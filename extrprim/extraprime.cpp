#include<iostream>
#include<fstream>
#define MAX 10000000
using namespace std;
ifstream f("extraprime.in");
ofstream g("extraprime.out");
int  p[]={1,10,100,1000,10000,100000,1000000,10000000},nr=1,nrmin,nrmax,nra;
char ciur[MAX];
int verifica(int);
int main()
{
    long a,b,i,j;
    f>>a>>b;
    nr=1;
         while(p[nr]<b)
     {
         nr++;
     }
     for(i=2;i<=p[nr];i++)
     {
         ciur[i]=1;
     }
       ciur[0]=ciur[1]=0;
     for(i=2;i*i<p[nr];i++)
     {
             if(ciur[i]==0) continue;
              for(j=i*i;j<p[nr];j+=i)
                  ciur[j]=0;
     }
     nra=0;
     for(i=a;i<=b;i++)
     {
         if(verifica(i)&&ciur[i])
         {
             nra++;
             if(nra==1)
                nrmin=i;
            nrmax=i;
         }
     }
     g<<nra<<"\n"<<nrmin<<"\n"<<nrmax;
    f.close();g.close();
    return 0;
}
int verifica(int x)
{
    int t=1,a;
    while(t<x)
    {
    a=x/10/t*t+x%t;
    if(ciur[a]==0)return 0;
    t*=10;
    }
    return 1;
}
