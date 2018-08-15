#include <fstream>
using namespace std;
ifstream f("numar.in");
ofstream g("numar.out");
long long n,k,maxim1,nrcfmax=1;
int este(long long x)
{
   long long i=0,v[7]={0},b[7]={0},j=1,nrc=0,nr=0,hold ;
   while(x!=0)
   {
       v[j]=x%10;
       x=x/10;
       if(v[j]==0)
       return 0;
       j++;
   }
   nrc=j-1;i=1;
   for(i=1;i<=nrc/2;i++)
   {
       hold=v[i];
       v[i]=v[nrc-i+1];
       v[nrc-i+1]=hold;
   }
   i=1;b[i]++;
   while(b[i]<2)
   {
        i=v[i]+i;
       i=i%nrc;
       if(i==0)
       i=nrc;
       b[i]++;
   }
   b[1]--;
   for(i=1;i<=7;i++)
   {
       if(b[i]==1)
       nr++;
   }
   if(nr==nrc)
   return 1;
   return 0;
}
void maxim(long long x)
{
   long long cx=x,i=0,b[10]={0},j=1,nr=0;
   while(x!=0)
   {
       b[x%10]++;
       x=x/10;
   }
   for(i=0;i<=9;i++)
   {
       if(b[i]>nr)
       nr=b[i];
   }
   if(nr>2)
   nr=2;
   if(nr>nrcfmax)
   {
       maxim1=cx;nrcfmax=nr;
   }
   else if(nr==nrcfmax)
   {
       if(cx>maxim1)
       maxim1=cx;
   }
}
int main()
{
    long long i,r[100],maimare,maimic,a,b;
    f>>n;
    for(i=1;i<=n;i++)
    {
        f>>r[i];
       maxim(r[i]);
    }
    g<<maxim1<<"\n";
    for(i=1;i<=n;i++)
    {
        maimare=maimic=r[i];
        while(este(maimare)==0)
        {
            maimare++;
        }
        while(este(maimic)==0&&maimic>0)
        {
            maimic--;
        }
        a=maimare-r[i];b=r[i]-maimic;
        if(a>b)
        {
            g<<maimic<<"\n";
        }
        else
        g<<maimare<<"\n";
    }
    f.close();g.close();
    return 0;
}
