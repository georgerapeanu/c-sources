#include <cstdio>
#include <cmath>
using namespace std;
FILE *f,*g;
int a,b,i,ci;
char s[2000];
long long c,nr=0;
int main()
{
    f=fopen("maxim.in","r");
    g=fopen("maxim.out","w");
    fscanf(f,"%d %d %d",&a,&b,&c);
    i=a;
    while(i<=b)
    {
        ci=i;
        if(c!=0)
        {
       if(1<=i&&i<=9)
       {
          if(i!=9)
          {
              ci=-1;
              c--;
          }
       }
       else if(10<=i&&i<=99)
       {
           if(i==99)
           {
                continue;
           }
           else if(i/10==9)
           {
              ci/=10;c--;
           }
           else if(i%10==9)
           {
                ci=9;c--;
           }
           else if(c%2==1)
           {
               if(c==1)
               {
                   if(ci/10>ci%10)
                   ci=ci/10;
                   else
                   ci=ci%10;
                   c=0;
               }
               else
               {
                   c-=2;
                   ci=-1;
               }
           }
           else
           {
              c-=2;
              ci=-1;
           }
       }
       else if(100<=i&&i<=999)
       {
           continue;
       }
       else if(1000<=i&&i<=9999)
       {
           continue;
       }
       else
       {
           if(c<5)
           {
               ci/=pow(10,c);
               if(ci==0)
               ci=-1;
           }
           else
           {ci=-1;c=0;}
       }
        }
       if(ci>=0)
       {
           if(ci>=1&&ci<=9)
           {
              s[nr++]+=ci+'0';
           }
           else if(ci>=10&&ci<=99)
           {
               s[nr++]+=ci/10+'0';
               s[nr++]+=ci%10+'0';
           }
           else if(ci>=100&&ci<=999)
           {
               s[nr++]+=ci/100+'0';
               s[nr++]+=ci/10%10+'0';
               s[nr++]+=ci%10+'0';
           }
           else if(ci>=1000&&ci<=9999)
           {
              s[nr++]+=ci/1000+'0';
              s[nr++]+=ci/100%10+'0';
              s[nr++]+=ci/10%10+'0';
              s[nr++]+=ci%10+'0';
           }
           else if(ci==10000)
           {
              s[nr++]+=1+'0';
              s[nr++]+=0+'0';
              s[nr++]+=0+'0';
              s[nr++]+=0+'0';
              s[nr++]+=0+'0';
           }
       }
       i++;
    }
    fprintf(g,"%s",s);
    fclose(g);
    fclose(f);
    return 0;
}
