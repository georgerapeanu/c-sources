#include <fstream>
#include <iostream>
using namespace std;
ifstream f("caleferata.in");
ofstream g("caleferata.out");
long long a,b,m,n,i,r[74000],t[74000],s=10,start,finish,s2,c,gasit,d;
int main()
{
    f>>a>>b>>m>>n;
    for(i=1;i<=n;i++)
    {
        f>>t[i]>>r[i];
//a
        s+=r[i];
        s+=t[i];
   //b
        if(i==a)
        {
            start=s-r[i];
        }
        if(i==(b-1))
          finish=s;
    //c
     if(i==1)
     {
         s2+=r[1];
         if(s2>m)
         {
             c=i;
             d=i+1;gasit=1;
         }
         if(s2==m)
         {
             c=i+1;gasit=1;
         }
     }
     else
     {
         s2+=t[i];
         if(s2>=m&&gasit==0)
         {c=i;gasit=1;}
         s2+=r[i];
         if(s2>m&&gasit==0)
         {
             c=i;d=i+1;gasit=1;
         }
         if(s2==m)
         {
             c=i+1;gasit=1;
         }
     }
    }
    g<<s<<"\n"<<(finish-start)<<"\n"<<c;
    if(d)
    g<<" "<<d;
    return 0;
}

