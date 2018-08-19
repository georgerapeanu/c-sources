#include <fstream>
using namespace std;
ifstream f("fisier.in");
ofstream g("fisier.out");
int v1[1001]={4,6,0,0,0},v2[1001]={2,2,5},N,v3[1001],c[1001];
void nrcifre()
{
    int i=1;
    while(v3[i]!=0)
    i++;
    v3[0]=i;
}
void resetare()
{
   for(int i=1;i<=v3[0];i++)
   v3[i]=0;
   v3[0]=0;
}
void decalaj2(bool nr)
{
    if(nr==true)
   {
     while(v2[1]==0)
     {
     for(int i=1;i<=v2[0];i++)
     v2[i]=v2[i+1];
     v2[0]--;
     }
   }
   else
   {
       while(v1[1]==0)
       {
      for(int i=1;i<=v1[0];i++)
     v1[i]=v1[i+1];
     v1[0]--;
       }
   }
}
void decalaj3()
{
    bool gasit=0;
     for(int i=2;i<=c[0]+1;i++)
     {
          if(c[i-1]!=0)
         {
             c[i]=c[i-1];
             if(gasit==0)
             {gasit=1;c[i-1]=0;}
         }
     }
     c[0]++;
}
void decalaj(int nr)
{
    bool gasit=false;
    if(nr==1)
   {
     for(int i=v2[0]+1;i>1;i--)
     {
             v2[i]=v2[i-1];
     }
     v2[0]++;
     v2[1]=0;
   }
   else if(nr==0)
   {
  for(int i=v1[0]+1;i>1;i--)
     {

             v1[i]=v1[i-1];

     }
     v1[0]++;
     v1[1]=0;
   }
   else
   {
       for(int i=v3[0]+1;i>1;i--)
     {
          v3[i]=v3[i-1];

     }
     v3[0]++;
     v3[1]=0;
   }
}
int comparare(int a[],int b[])
{
    if(a[0]==b[0])
   for(int i=1;i<=b[0];i++)
   {
       if(a[i]>b[i])
       return 1;
       if(a[i]<b[i])
       return 2;
   }
   return 0;
}
void adunare()
{
   if(v1[0]>v2[0])
       while(v1[0]>v2[0])
       decalaj(1);
   if(v2[0]>v1[0])
   while(v2[0]>v1[0])
       decalaj(0);
   for(int i=v1[0];i>0;i--)
   {
       v1[i]+=v2[i];
       if(v1[i]>=10)
       {
           v1[i-1]+=v1[i]/10;
           v1[i]%=10;
       }
   }
   if(v1[1]>10)
   {
       decalaj(0);
       v1[1]=v1[2]/10;
       v1[2]%=10;
   }
}
void scadere()
{
      if(v1[0]>v2[0])
       while(v1[0]>v2[0])
       decalaj(1);
   if(v2[0]>v1[0])
   while(v2[0]>v1[0])
       decalaj(0);
   if(comparare(v1,v2)==0)
   {
       v1[0]=1;
       v1[1]=0;
   }
   else if(comparare(v1,v2)==1)
   {
       for(int i=v1[0];i>0;i--)
       {
           v1[i]-=v2[i];
           {
               v1[i]+=10;
               v1[i-1]--;
           }
       }
       if(v1[1]==0)
       decalaj2(0);
   }
   else
   {
       for(int i=v2[0];i>0;i--)
       {
           v2[i]-=v1[i];
           if(v2[i]<0)
           {
               v2[i]+=10;
               v2[i-1]--;
           }
       }
       if(v2[1]==0)
       decalaj2(1);
       for(int i=0;i<=v2[0];i++)
       v1[i]=v2[i];
   }
}
void inmultire()
{
    resetare();
    v3[0]=v1[0]+v2[0]-1;
    for(int i=1;i<=v1[0];i++)
    {
        for(int j=1;j<=v2[0];j++)
        {
              v3[i+j-1]+=v1[i]*v2[j];
        }
    }
    for(int i=v3[0];i>1;i--)
    {
        v3[i-1]+=v3[i]/10;
        v3[i]%=10;
    }
    while(v3[1]>10)
    {
       decalaj(2);
       v3[1]=v3[2]/10;
       v3[2]%=10;
    }
}
void impartire()
{
    c[0]=1;
       while(comparare(v1,v2)>=0)
       {
           c[1]++;
           scadere();
       }
       while(c[1]>10)
       {
           decalaj3();
           c[1]=c[2]/10;
           c[2]=c[2]%10;
       }
}
void sqrt()
{

}
void cbrt()
{

}
void krt(int k)
{

}
void plasare(long long s, long long f)
{

}
int sq()
{
    inmultire();
}
void cb()
{
    inmultire();
     inmultire();
}
void k(int k)
{
      for(int i=1;i<=k;i++)
  inmultire();
}
int main()
{
     impartire();
     for(int i=1;i<=c[0];i++)
     g<<c[i];
    return 0;
}
