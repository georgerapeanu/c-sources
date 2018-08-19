#include <fstream>
#include <cmath>
#include <cstring>
using namespace std;
ifstream f("input.in");
ofstream g("input.out");
long v[5242881]={1,1};
long long n[200000];
void shl()
{
        while(v[1]==0)
        {
            for(long i=1;i<v[0];i++)
            v[i]=v[i+1];
            v[v[0]]=0;
            v[0]--;
        }
}
void shr()
{
     for(int i=v[0]+1;i>1;i--)
     v[i]=v[i-1];
     v[1]=0;
}
void shr2()
{
     for(int i=n[0]+1;i>1;i--)
     n[i]=n[i-1];
     n[1]=0;
}
void inmultire(int x)
{
      for(long i=1;i<=v[0];i++)
      v[i]=v[i]*x;
      for(long i=v[0];i>=2;i--)
      if(v[i]>=10)
      {
          v[i-1]+=v[i]/10;
          v[i]%=10;
      }
      while(v[1]>10)
      {
           shr();
           v[1]=v[2]/10;
           v[2]%=10;
           v[0]++;
      }
}
void pb2()
{
    int n;long x,nrminus=0;
    f>>n;
    for(int i=1;i<=n;i++)
    {
        f>>x;
        if(x<0)
        {nrminus++;x*=-1;}
        inmultire(x);
    }
    char c[200];
    for(int i=0;i<=199;i++)
    c[i]=0;
    if(nrminus%2==0)
    {
        for(int i=1;i<=v[0];i++)
        c[i-1]=v[i]+'0';
    }
    else
    {
        for(int i=1;i<=v[0];i++)
        {
            c[i]=v[i]+'0';
        }
        c[0]='-';
    }
    g<<c;
}
int prime(long nr)
{
    if(nr<2)  return 0;
    for(long i=2;i<=int(sqrt(nr));i++)
    if(nr%i==0) return 0;
    return 1;
}
void pb1()
{
    long n,pi=1,bi=0,ci,j;
    bool gasit;
    f>>n;
     for(long i=n;i>=1;i--)
     {
        if(prime(i)==0)
        {
            gasit=0;
            for(j=9;j>=2;j--)
            {
                ci=i;bi=0;pi=1;
                 while(ci!=0)
                 {
                     bi+=pi*(ci%j);
                     pi*=10;
                     ci/=j;
                 }
                 if(prime(bi)==1)
                 gasit=1;
                 if(gasit==1)
                break;
            }
            if(gasit==1)
            g<<i<<" "<<j<<"\n";
        }
     }
}
void pb3()
{
   long k,n,nr1,nr[200][200];
   bool used[200]={0};
   f>>n>>k;
   for(int i=0;i<200;i++)
   {nr[i][0]=1;}
   for(int i=0;i<200;i++)
   for(int j=1;j<200;j++)
   nr[i][j]=0;
   for(long int i=1;i<=n;i++)
   {
       for(long int j=1;j<=k;j++)
       {
           f>>nr1;
           if(nr[nr1][nr[nr1][0]-1]!=i||nr[nr1][0]-1==0)
           nr[nr1][nr[nr1][0]++]=i;
       }
   }
   nr1=0;
   bool gasit=0;
   for(long i=1;i<=n;i++)
   {
       gasit=false;
       for(long j=1;j<nr[i][0];j++)
       {
           if(used[nr[i][j]]==1)
           {gasit=true;break;}
       }
       if(gasit==false&&nr[i][0]!=1)
       {
            for(long j=1;j<nr[i][0];j++)
            {
                 used[nr[i][j]]=1;
                 g<<nr[i][j]<<" ";
            }
            g<<"\n";
       }
   }
}
void pb2e()
{
    long long pozplec=0,pozstop,n,v1[2000]={0},v2[2000]={0},i=0;
    f>>n;pozstop=n-1;
    while(i<n)
    f>>v1[i++];
    i=0;
    while(i<n)
    f>>v2[i++];
    i=0;
    while(v1[i]==v2[i])
    i++;
    pozplec=i;
    i=n-1;
    while(v1[i]==v2[i])
    i--;
    pozstop=i;
    g<<(pozplec+1)<<" "<<(pozstop+1);
}
int palindrom(long long dim)
{
    for(long long i=1;i<=dim/2;i++)
    {
        if(v[i]!=v[dim-i+1])
        return 0;
    }
    return 1;
}
void adunare()
{
    long long a,b;
      for(long long i=1;i<=n[0]/2;i++)
      {
          a=n[i];
          b=n[v[0]-i+1];
          n[i]+=b;
          n[v[0]-i+1]+=a;
      }
      for(long long i=n[0];i>=2;i--)
      {n[i-1]+=n[i]/10;n[i]%=10;}
      while(n[1]>10)
      {
          shr2();
          n[1]+=n[2]/10;n[2]%=10;
      }
}
void pb3e()
{
    char n0[20000];
    long long n[20000],k,nrdati=0,i;
    bool gasit=0;
    f.getline(n0,20000);
    for(i=0;i<strlen(n0);i++)
    {
        n[i+1]=n0[i]-'0';n[0]++;
    }
    f>>k;i=1;
    while(i<=k)
    {
         adunare();
         if(palindrom(v[0])==1)
         {
             gasit=1;break;
         }
         i++;
    }
    if(gasit==1)
    g<<(i-1)<<"\n"<<n;
    else
    g<<"nu";
}
int main()
{
    pb3e();
    f.close();g.close();
    return 0;
}
